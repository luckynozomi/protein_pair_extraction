//
// Created by Xin Sui on 3/1/18.
//

#ifndef STRING_PARSING_TEST_TRIE_BUILDER_H
#define STRING_PARSING_TEST_TRIE_BUILDER_H

#include "aho_corasick.hpp"
#include <boost/filesystem.hpp>

aho_corasick::trie trie_builder(const boost::filesystem::path&,
                                std::string (*formatting_func)(const std::string&));
aho_corasick::trie trie_builder(const std::vector<std::string>&,
                                std::string (*formatting_func)(const std::string&));


#endif //STRING_PARSING_TEST_TRIE_BUILDER_H
