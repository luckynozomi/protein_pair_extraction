#include <iostream>
#include "aho_corasick.hpp"
#include <fstream>
#include <chrono>
#include <string>
#include <regex>
#include <numeric>

int main() {
    std::cout.sync_with_stdio(false);


    aho_corasick::trie trie;

    std::ifstream protein_names;
    protein_names.open("/Users/xinsui/CLionProjects/protein_pair_extraction/data/MyUniqProNames.txt", std::ios::in);
    // protein_names.unsetf(std::ios_base::skipws);
    std::string protein_name;

    std::vector<std::string> ProNameVec;

    long number_of_lines = 0;
    while(getline(protein_names, protein_name)) {
        ProNameVec.push_back(protein_name);
        for(std::string::iterator c = protein_name.begin(); c != protein_name.end(); ++c){
            *c = std::tolower(*c);
        }
        ++number_of_lines;
        trie.insert(" " + protein_name + " ");
    }
    protein_names.close();
    trie.case_insensitive();

    std::vector<long> occurences(number_of_lines);

    std::ifstream abstracts;
    abstracts.open("/Users/xinsui/CLionProjects/protein_pair_extraction/data/pubmed_abstracts_2016.out", std::ios::in);
    std::string abstract;

    long lines = 0;

    while(getline(abstracts, abstract)){

        if(++lines == 100 * 1000)
            break;

        aho_corasick::trie::emit_collection results;

        abstract[abstract.length() - 1] = ' ';

        results = trie.parse_text(" " + abstract);

        for (auto& item : results){
            ++occurences[item.get_index()];
        }

    }

    std::vector<long> indexes(number_of_lines);

    std::iota(indexes.begin(), indexes.end(), 0);

    std::sort(indexes.begin(), indexes.end(),
              [&](long t1, long t2) -> bool{
                  return occurences[t1] > occurences[t2];
              });


    long threshold = 100;
    for(int j = 0; j != threshold; ++j){
        std::cout << indexes[j] << ' ' << occurences[indexes[j]] << '\n';
    }

    std::ofstream protein_names_out;
    protein_names_out.open("/Users/xinsui/CLionProjects/protein_pair_extraction/data/MyUniqProNamesFiltered.txt", std::ios::out);

    for(int j = 0; j != number_of_lines; ++j){
        if(occurences[j] == 0)
            protein_names_out << ProNameVec[j]  << std::endl;
    }


    return 0;

}
