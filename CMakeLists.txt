cmake_minimum_required(VERSION 3.9)
project(protein_pair_extraction)

set(CMAKE_CXX_STANDARD 17)

find_package( Boost REQUIRED filesystem system)

set(CMAKE_CXX_FLAG '-march=native')

add_executable(protein_pair src/protein_pair_extraction.cpp src/utils.cpp src/utils.h src/trie_builder.cpp src/trie_builder.h)
add_executable(protein_filter src/filter.cpp src/utils.cpp src/utils.h src/trie_builder.cpp src/trie_builder.h)

#add_executable(protein_pair_extraction src/main.cpp)

target_link_libraries(protein_pair ${Boost_LIBRARIES})
target_link_libraries(protein_filter ${Boost_LIBRARIES})
