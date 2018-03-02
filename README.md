# Multiple String Matching
This project uses [Aho-Corasick algorithm](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm) to find lines in a target file that matches one or more strings in the dictionary file.

## Objective
This project aims to achieve three objectives:
1. Dictionary filtering: filter the words in the string dictionary by several documents so the filtered dictionary does not contain common words.
2. Single matching: output the lines in the target file that matches one or more words in the string dictionary.
3. Double matching: output the lines in the target file that matches two or more words in the string dictionary.

This project uses a self-modified implementation of Aho-Corasick algorithm on [Github page](https://github.com/cjgdev/aho_corasick).

## Prerequisite
[Cmake](https://cmake.org/install/)

[Boost](http://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html)

## Installation
```
 git clone https://github.com/suixin661014/protein_pair_extraction
 cd protein_pair_extraction
 mkdir build && cd build 
 cmake -DCMAKE_BUILD_TYPE=Release ..
 make
```

## Usage
The code builds two executables: 1) protein_filter and 2) protein_pair.
It is suggested to move the two executables to the directory where the dictionary file (protein name dictionary) and the target file (senteces of abstracts) are.
```
./protein_filter protein_name_file [threshold] [output]
```
will filter the dictionary ```protein_name_file``` using all ```.txt``` files in subdirectory ```filter``` as targets. An entry in the dictrionary will be removed if it occures more than ```threshold``` times in any of those files. The result will be printed out to ```output```.
By default, ```threshold=1``` and ```output=stdout```.
```
./protein_pair protein_name_file pubmed_abstract_file [output]
```
will find sentences in target ```pubmed_abstract_file``` that contains 2+ entries in ```protein_name_file```, and write output to ```output```.
By default, ```output=stdout```.

## Limitation
The current version does not implement single matching, because there is no time.
The target files, e.g, ```pubmed_abstract_file``` should contain the following format "label \t sentence". 
The aforementioned sentence should be word-separated, that "ABC, DEF." should be pre-processed into "ABC , DEF ."

## Known issues
The implementation of Aho-Corasick algorithm stores local objects when there is a matching, and thus will suffer from performance issues when each sentence is too long. 
It's implementation of "only_whole_words()" is also not efficient. There is a work-around, but we will continue to use it as long as it gives acceptable performance.

