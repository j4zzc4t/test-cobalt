#include <istream>
#include <memory.h>
#include <list>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include "comparator.hxx"

int main(){

    std::string input;
    std::cout << "Please give me the word to compare others to" << std::endl; 
    std::cin >> input;
    Comparator comp;

    std::vector<std::string> words{"Michelle", "Oliver", "Elliot", "Midge", "Jack", "Grzegorz", "Brzemchyszczykewicz"};

    auto result = comp.find_similar(input, words);
    std::cout << "Here are the results:" << std::endl;
    for (auto word : result )
    {
        std::cout << word << std::endl; 
    }   
    return 0;
}

