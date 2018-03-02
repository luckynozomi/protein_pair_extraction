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

std::vector<std::string> protein_name_vec_builder(const boost::filesystem::path& protein_name_path,
                                                  std::string (*formatting_func)(const std::string&))

{
    boost::filesystem::ifstream protein_name_file;
    protein_name_file.open(protein_name_path, std::ios::in);
    std::vector<std::string> ProNameVec;
    std::string protein_name;
    while(getline(protein_name_file, protein_name))
        ProNameVec.push_back(formatting_func(protein_name));
    return ProNameVec;

}

void filter(const boost::filesystem::path& target_file_path, std::vector<std::string>& ProNameVec,
                             std::string (*formatting_func)(const std::string&), long threshold)
{

    std::vector<long> occurences(ProNameVec.size());

    aho_corasick::trie trie = trie_builder(ProNameVec, formatting_func);
    trie.remove_overlaps().only_whole_words();

    boost::filesystem::ifstream target_file;
    target_file.open(target_file_path, std::ios::in);
    long line_number = 0;
    std::string sentence, pubmed_index;
    while(getline(target_file, sentence))
    {
        ++line_number;

        aho_corasick::trie::emit_collection results = trie.parse_text(sentence);

        for (auto& item : results) {
            ++occurences[item.get_index()];
        }

    }

    auto new_end = std::remove_if(ProNameVec.begin(), ProNameVec.end(),
                       [&](const std::string& item) -> bool
                       {
                           auto index = &item - &*ProNameVec.begin();
                           return occurences[index] >= threshold;
                       });

    ProNameVec.erase(new_end);

}


int main(int argc, char* argv[]){

    boost::filesystem::path working_dir = boost::filesystem::current_path();
    boost::filesystem::path protein_name_path = "ProtNames.txt";
    boost::filesystem::path output_data_path = "STDIO";
    long threshold = 1;

    if(!boost::filesystem::is_directory(working_dir)){
        std::cerr << working_dir << " is not a directory.\n";
        return 1;
    }

    switch(argc){
        case 4:
            output_data_path = argv[3];
        case 3:
            try {
                threshold = boost::lexical_cast<long>(argv[2]);
            } catch( boost::bad_lexical_cast const& ) {
                std::cerr << argv[2] << " is not an integer.\n";
                return 1;
            }
        case 2:
            protein_name_path = argv[1];
            break;
        default:
            std::cout << "Using default settings. \n";
    }


    if( !boost::filesystem::exists(working_dir / protein_name_path) ) {
        std::cerr << working_dir / protein_name_path << " doesn't exist. \n";
        std::cerr << "Usage:  protein_name_file [threshold, default=1] [output_file]\n";
        return 1;
    }


    std::string (*formatting_func)(const std::string&) = identity_formatting_func;
    std::vector<std::string> ProNameVec = protein_name_vec_builder(protein_name_path, formatting_func);
    for(auto& file : boost::filesystem::directory_iterator(working_dir / "filter"))
    {
        if(file.path().filename() == "regex.txt"){
        } else if (file.path().extension() == ".txt") {
            filter(file.path(), ProNameVec, formatting_func, 1);
        }
    }


    if (output_data_path == "STDIO") {
        for(const auto& protein_names : ProNameVec)
            std::cout << protein_names << std::endl;
    } else {
        boost::filesystem::ofstream output_file (working_dir / output_data_path, std::ios::out);
        for(const auto& protein_names : ProNameVec)
            output_file << protein_names << std::endl;
        output_file.close();
    }


    return 0;


}