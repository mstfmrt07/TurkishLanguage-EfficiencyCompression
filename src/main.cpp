//
// Created by Mustafa Mert Aladağ on 18.11.2024.
//

#include <unordered_map>
#include <iostream>

#include "Utils.h"
#include "Node.h"
#include "HuffmanTree.h"
#include "TextOperations.h"

std::unordered_map<char, int> getFrequencyMap(const std::string &str)
{
    std::unordered_map<char, int> frequencyMap;
    for (char c: str)
    {
        frequencyMap[c]++;
    }

    return frequencyMap;
}

int main()
{
    std::cout << "Reading the sample text: \n " << benchmark(TimeUnit::MILLISECONDS, &TextOperations::read, "../resources/turkish_cities_wiki.txt") << "\n";

    std::string str = TextOperations::read("../resources/turkish_cities_wiki.txt");

    std::wstring wstr = TextOperations::utf8_to_wstring(str);

    // Size of the unfiltered and unmodified sample text.
    std::cout << "Size of the sample text: " << wstr.size() << std::endl << std::endl;

    auto filteredStr = TextOperations::filterTurkishText(wstr);

    TextOperations::write(filteredStr, "../resources/filtered_turkish_cities_wiki.txt");

    // Size of the filtered and modified sample text.
    std::cout << "Size of the filtered text: " << filteredStr.size() << std::endl;

    std::cout << "Elapsed milliseconds for frequency map: \n" << benchmark(TimeUnit::MILLISECONDS, getFrequencyMap, filteredStr) << "\n";

    std::unordered_map<char, int> frequencyMap = getFrequencyMap(filteredStr);
    std::cout << "Frequency Map: \n";
    for (const auto &pair: frequencyMap)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    HuffmanTree huffmanTree(frequencyMap);
    Node* rootNode = huffmanTree.getRootNode();
    std::cout << "Root node of the Huffman tree: " << rootNode->data << " - " << rootNode->freq << std::endl;

    return 0;
}