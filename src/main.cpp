//
// Created by Mustafa Mert Aladağ on 18.11.2024.
//

#include <unordered_map>
#include <iostream>

#include "Utils.h"
#include "Node.h"
#include "HuffmanTree.h"
#include "TextReader.h"

std::unordered_map<char, int> getFrequencyMap(const std::string &str)
{
    std::unordered_map<char, int> frequencyMap;
    for (char c: str)
    {
        frequencyMap[c]++;
    }

    return frequencyMap;
}

void read(TextReader& textReader)
{
    textReader.read();
}

int main()
{
//    std::string str = "aaaabbbccddddeeefa";
    TextReader textReader("../resources/text.txt");

    std::cout << "Reading the sample text: \n " << benchmark(TimeUnit::MILLISECONDS, read, textReader) << "\n";

    std::string str = textReader.read();
    std::cout << str << std::endl;

    // Size of the unfiltered and unmodified sample text.
    std::cout << "Size of the sample text: " << str.size() << std::endl;

    std::cout << "Elapsed milliseconds for frequency map: \n" << benchmark(TimeUnit::MILLISECONDS, getFrequencyMap, str) << "\n";

    std::unordered_map<char, int> frequencyMap = getFrequencyMap(str);
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