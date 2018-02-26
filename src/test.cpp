//
// Created by Xin Sui on 2/22/18.
//

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

int main() {
    std::ifstream abstracts;
    abstracts.open("/Users/xinsui/CLionProjects/protein_pair_extraction/data/pubmed_abstracts_2016.out", std::ios::in);
    // abstracts.unsetf(std::ios_base::skipws);
    std::string abstract;

    while(getline(abstracts, abstract)){
        if(abstract.empty())
            continue;

        const long number_start = 0;
        long number_end = abstract.find_first_not_of("0123456789");
        const std::string number = abstract.substr(number_start, number_end - number_start);

        long year_start = abstract.find_first_of("0123456789", number_end);
        long year_end = abstract.find_first_not_of("0123456789", year_start);
        const std::string year = abstract.substr(year_start, year_end - year_start);

        std::cout << "Number: " << number << std::endl;
        std::cout << "Year: " << year << std::endl;

        long sentence_start = abstract.find_first_not_of(" \t", year_end);
        abstract = abstract.substr(sentence_start);

        std::smatch match;
        std::regex reg("[.!?][ ][0-9A-Z]");
        auto words_begin = std::sregex_iterator(abstract.begin(), abstract.end(), reg);
        auto words_end = std::sregex_iterator();

        std::cout << "Found " << std::distance(words_begin, words_end) << " sentences:" << std::endl;
        long start = 0;
        long length;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            length = i->position() + 1 - start; // Start of sentence to the sentence ender [.!?] (included)
            std:: cout << abstract.substr(start, length) << std::endl;
            start += length + 1; // The position where the start of the next sentence is.
        }

    }



    return 0;
}
