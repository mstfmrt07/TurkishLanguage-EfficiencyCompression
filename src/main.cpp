//
// Created by Mustafa Mert Aladağ on 18.11.2024.
//

#include <map>
#include <iostream>

#include "Utils.h"

void printCharFrequencies(const std::string &str)
{
    std::map<char, int> frequencyMap;
    for (char c: str)
    {
        frequencyMap[c]++;
    }

    std::map<int, std::vector<char>> sortedCharFrequencies;
    for (const auto &pair: frequencyMap)
    {
        sortedCharFrequencies[pair.second].push_back(pair.first);
    }

    for (const auto &pair: sortedCharFrequencies)
    {
        for (char c: pair.second)
        {
            std::cout << c << ": " << pair.first << std::endl;
        }
    }
}


int main()
{
    std::string str = "aaaabbbccddddeeefa";
    std::cout << str << std::endl;

    std::cout<<"Elapsed milliseconds: \n"<<benchmark(TimeUnit::MILLISECONDS, printCharFrequencies, str )<<"\n";
    return 0;
}