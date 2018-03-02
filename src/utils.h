//
// Created by Xin Sui on 3/1/18.
//

#ifndef STRING_PARSING_TEST_UTILS_H
#define STRING_PARSING_TEST_UTILS_H

#include <string>

std::string identity_formatting_func(const std::string&);
std::string albert_formatting_func(const std::string&);

bool parse_sentence(std::string&, std::string&, char deliminator='\t');


#endif //STRING_PARSING_TEST_UTILS_H
