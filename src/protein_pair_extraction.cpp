//
// Created by Xin Sui on 3/2/18.
//

//
// Created by Xin Sui on 3/2/18.
//

#include "filter.h"
#include "utils.h"
#include "aho_corasick.hpp"
#include "trie_builder.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <numeric>

long myisspace(long acc, char c)
{
    return acc + (long)isspace(c);
}

std::string result_string(const aho_corasick::trie::emit_collection& results, const std::string& sentence)
{
    std::stringstream ret;
    for(const auto& item : results)
    {
        ret << '|' << item.get_keyword() << '_' << std::accumulate(sentence.begin(), sentence.begin() + item.get_end(), 1, myisspace);
    }
    ret << '\t' << sentence;
    return ret.str();
}

void protein_pair(const boost::filesystem::path& target_file_path, const boost::filesystem::path& dictionary_file_path,
            std::string (*formatting_func)(const std::string&), std::ostream& ostream)
{


    aho_corasick::trie trie = trie_builder(dictionary_file_path, formatting_func);
    trie.remove_overlaps().only_whole_words();

    boost::filesystem::ifstream target_file;
    target_file.open(target_file_path, std::ios::in);
    long line_number = 0;
    std::string sentence, pubmed_index;
    while(getline(target_file, sentence))
    {
        ++line_number;

        if(!parse_sentence(sentence, pubmed_index)){
            std::cerr << line_number << " does not contain a valid sentence. \n";
            continue;
        }

        aho_corasick::trie::emit_collection results = trie.parse_text(sentence);

        if(results.size() >= 2)
            ostream << pubmed_index + "\t" + result_string(results, sentence) + "\n";

    }


}


int main(int argc, char* argv[]){

    boost::filesystem::path working_dir = boost::filesystem::current_path();
    boost::filesystem::path protein_name_path = "ProtNames.txt";
    boost::filesystem::path pubmed_abstract_path = "pubmed_abstracts_2016.out";
    boost::filesystem::path output_data_path = "STDIO";

    switch(argc){
        case 4:
            output_data_path = argv[3];
        case 3:
            pubmed_abstract_path = argv[2];
            protein_name_path = argv[1];
            break;
        default:
            std::cout << "Using default settings. \n";
    }


    if( !boost::filesystem::exists(working_dir / protein_name_path) ) {
        std::cerr << working_dir / protein_name_path << " doesn't exist. \n";
        std::cerr << "Usage:  protein_name_file pubmed_abstract_file [output_file]\n";
        return 1;
    }

    if( !boost::filesystem::exists(working_dir / pubmed_abstract_path) ) {
        std::cerr << working_dir / pubmed_abstract_path << " doesn't exist. \n";
        std::cerr << "Usage:  protein_name_file pubmed_abstract_file [output_file]\n";
        return 1;
    }



    std::string (*formatting_func)(const std::string&) = albert_formatting_func;

    if (output_data_path == "STDIO") {
        protein_pair(pubmed_abstract_path, protein_name_path, formatting_func, std::cout);
    } else {
        boost::filesystem::ofstream output_file (working_dir / output_data_path, std::ios::out);
        protein_pair(pubmed_abstract_path, protein_name_path, formatting_func, output_file);
        output_file.close();
    }


    return 0;


}