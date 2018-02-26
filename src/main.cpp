#include <iostream>
#include "aho_corasick.hpp"
#include <fstream>
#include <chrono>
#include <string>
#include <regex>

int main() {
    std::cout.sync_with_stdio(false);


    aho_corasick::trie trie;

    std::ifstream protein_names;
    protein_names.open("/Users/xinsui/CLionProjects/protein_pair_extraction/data/UniProtNames.txt", std::ios::in);
    // protein_names.unsetf(std::ios_base::skipws);
    std::string protein_name;
    while(getline(protein_names, protein_name)) {
        for(std::string::iterator c = protein_name.begin(); c != protein_name.end(); ++c){
            *c = std::tolower(*c);
        }
        trie.insert(" " + protein_name + " ");
    }

    protein_names.close();
    trie.case_insensitive();



    std::ifstream abstracts;
    abstracts.open("/Users/xinsui/CLionProjects/protein_pair_extraction/data/pubmed_abstracts_2016.out", std::ios::in);
    std::string abstract;

    long line_num = 0;
    long num_wo_data = 0;
    auto start = std::chrono::steady_clock::now();

    while(getline(abstracts, abstract)){

        ++line_num;

        if(abstract.empty())
            continue;

        static const std::string alnum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        const long number_start = 0;
        long number_end = abstract.find_first_not_of("0123456789");
        const std::string number = abstract.substr(number_start, number_end - number_start);

        long year_start = abstract.find_first_of(alnum, number_end);
        long year_end = abstract.find_first_not_of(alnum, year_start);
        const std::string year = abstract.substr(year_start, year_end - year_start);

        // std::cout << "Number: " << number << std::endl;
        // std::cout << "Year: " << year << std::endl;

        long sentence_start = abstract.find_first_not_of(" \t", year_end);

        if(sentence_start == -1){
            //std::cerr << line_num << ' ';
            ++num_wo_data;
            //if((num_wo_data % 10) == 0)
                //std::cerr << std::endl;
            continue;
        }

        if(line_num == 1000)
            break;

        abstract = abstract.substr(sentence_start);

        std::smatch match;
        std::regex reg("[.!?][ ][0-9A-Z]");
        auto words_begin = std::sregex_iterator(abstract.begin(), abstract.end(), reg);
        auto words_end = std::sregex_iterator();

        // std::cout << "Found " << std::distance(words_begin, words_end) << " sentences:" << std::endl;
        long start = 0;
        long length;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            length = i->position() + 1 - start; // Start of sentence to the sentence ender [.!?] (included)
            // std::cout << abstract.substr(start, length) << std::endl;

            aho_corasick::trie::emit_collection results;

            std::string sentence = abstract.substr(start, length);

            sentence[sentence.length() - 1] = ' ';

            results = trie.parse_text(" " + sentence);

            if(results.size() >= 2)
                //std::cout << abstract.substr(start, length) << '\n';
                std::cout << "t";

            start += length + 1; // The position where the start of the next sentence is.
        }


    }


    auto end = std::chrono::steady_clock::now();
    std::cout << "\nTime: " << std::chrono::duration_cast<std::chrono::seconds> (end-start).count() << std::endl;
    std::cerr << num_wo_data << std::endl;

    return 0;

}
