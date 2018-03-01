//
// Created by Xin Sui on 2/26/18.
//

#include <string>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string/trim.hpp>
int main() {

    std::ifstream xml_file;
    xml_file.open("/Users/xinsui/CLionProjects/protein_pair_extraction/data/interactorList.xml", std::ios::in);
    std::string line;

    const std::string range_begin = "<interactorList>";
    const std::string range_end = "</interactorList>";

    const std::string semi_range_begin = "<interactor id="; // in this
    const std::string semi_range_end = "</interactor>"; // in this

    bool in_range = false;

    while (getline(xml_file, line)) {

        boost::trim(line);

        if (!strcmp(line.data(), range_begin.data())) { break; }
    }

    do {
        while (getline(xml_file, line)) {
            boost::trim(line);

            if (!strncmp(line.data(), semi_range_begin.data(), semi_range_begin.size())) { std::cout << line << std::endl; break; }
        }

        while (getline(xml_file, line)) {
            boost::trim(line);
            if (!strcmp(line.data(), "<names>")) { break; }
        }

        while (getline(xml_file, line)) {
            boost::trim(line);
            if (!strcmp(line.data(), "</names>")) { break; }
            std::cout << line << std::endl;
        }


        while (getline(xml_file, line)) {
            boost::trim(line);
            if ( !strcmp(line.data(), semi_range_end.data()) ) {
                break;
            }
        }

    } while ( line != "" );



    return 0;
}