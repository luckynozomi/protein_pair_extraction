#include <iostream>
#include "aho_corasick.hpp"
#include <fstream>
#include <chrono>

int main() {

    aho_corasick::trie trie;

    auto start = std::chrono::steady_clock::now();

    std::ifstream protein_names;
    protein_names.open("/Users/xinsui/CLionProjects/string_parsing_test/data/UniProtNames.txt", std::ios::in);
    protein_names.unsetf(std::ios_base::skipws);
    std::string protein_name;
    while(getline(protein_names, protein_name)) {
        for(std::string::iterator c = protein_name.begin(); c != protein_name.end(); ++c){
            if( isalnum((unsigned char)*c) == 0 )
                *c = '_';
            else
                *c = std::tolower(*c);
        }
        trie.insert("_" + protein_name + "_");
    }
    protein_names.close();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time for building trie: " << std::chrono::duration_cast<std::chrono::seconds> (end-start).count() << std::endl;
    start = end;

    trie.case_insensitive();

    std::ifstream abstracts;
    abstracts.open("/Users/xinsui/CLionProjects/string_parsing_test/data/pubmed_abstracts_2016.out", std::ios::in);
    abstracts.unsetf(std::ios_base::skipws);

    std::istream_iterator<char> char_abstracts(abstracts);



    end = std::chrono::steady_clock::now();
    std::cout << "Time for reading file for parsing: " << std::chrono::duration_cast<std::chrono::seconds> (end-start).count() << std::endl;
    start = end;


     trie.parse_text(char_abstracts);


    end = std::chrono::steady_clock::now();
    std::cout << "Time for parsing: " << std::chrono::duration_cast<std::chrono::seconds> (end-start).count() << std::endl;

    return 0;

}
