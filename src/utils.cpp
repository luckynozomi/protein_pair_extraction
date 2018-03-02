//
// Created by Xin Sui on 3/1/18.
//

#include "utils.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <iostream>

std::string identity_formatting_func(const std::string& str)
{
    return boost::trim_copy(str);
}

std::string albert_formatting_func(const std::string& str)
{
    std::string replaced = boost::algorithm::replace_all_copy(str, "/", " / ");
    boost::trim(replaced);
    std::regex redundant_spaces("\\s+");
    return std::regex_replace(replaced, redundant_spaces, " ");
}




bool parse_sentence(std::string& sentence, std::string& pubmed_index, char deliminator){
    boost::trim(sentence);
    auto index = sentence.find_first_of(deliminator);
    if(index == std::string::npos)
        return false;
    pubmed_index = sentence.substr(0,index);
    sentence = sentence.substr(index+1);
    if(sentence.empty())
        return false;
    return true;
}
