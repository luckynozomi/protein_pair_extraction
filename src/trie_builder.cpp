//
// Created by Xin Sui on 3/1/18.
//

#include "trie_builder.h"
#include <boost/filesystem/fstream.hpp>
#include <string>

aho_corasick::trie trie_builder(const boost::filesystem::path& protein_name_path,
                                std::string (*formatting_func)(const std::string&))
{
    boost::filesystem::ifstream protein_name_file;
    protein_name_file.open(protein_name_path, std::ios::in);
    aho_corasick::trie trie;
    std::string protein_name;
    while(getline(protein_name_file, protein_name))
        trie.insert(formatting_func(protein_name));
    protein_name_file.close();
    return trie;
}

aho_corasick::trie trie_builder(const std::vector<std::string>& ProNameVec,
                                std::string (*formatting_func)(const std::string&))
{
    aho_corasick::trie trie;
    for (const auto& protein_name : ProNameVec) {
        trie.insert(formatting_func(protein_name));
    }
    return trie;
}