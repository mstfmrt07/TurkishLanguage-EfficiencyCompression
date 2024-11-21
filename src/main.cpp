//
// Created by Mustafa Mert Aladağ on 18.11.2024.
//

#include <map>
#include <iostream>

#include "Utils.h"
#include "Node.h"
#include "HuffmanTree.h"
#include "TextOperations.h"

std::map<char, int> getFrequencyMap(const std::string &str)
{
    std::map<char, int> frequencyMap;
    for (char c: str)
    {
        frequencyMap[c]++;
    }

    return frequencyMap;
}

int main()
{
    auto startTime = __timeNow();

    std::string str = TextOperations::read("../resources/cities_wiki.txt");

    std::wstring wstr = TextOperations::utf8_to_wstring(str);

    // Size of the unfiltered and unmodified sample text.
    std::cout << "Size of the sample text: " << wstr.size() << std::endl << std::endl;

    auto filteredStr = TextOperations::filterTurkishText(wstr);

    TextOperations::write(filteredStr, "../resources/filtered_cities_wiki.txt");
    // Size of the filtered and modified sample text.
    std::cout << "Size of the filtered text: " << filteredStr.size() << std::endl;

    // Build frequency table
    std::map<char, int> frequencies = getFrequencyMap(filteredStr);

    // Build tree
    HuffmanTree tree(frequencies);
    Node* root = tree.getRootNode();

    // Generate codes
    std::map<char, std::string> codes;
    tree.generateCodes(root, "", codes);

    // Print codes
    for (auto p : codes)
    {
        std::cout << p.first << " : " << p.second << std::endl;
    }

    std::string encodedText = tree.encodeToString(filteredStr, codes);
//    std::cout << "Encoded text: " << encodedText << std::endl;

    TextOperations::write(encodedText, "../resources/encoded_text.txt");

    tree.encodeToBinary(filteredStr, codes, "../resources/encoded_text.bin");

    std::string decodedText = tree.decodeFromString(encodedText, root);
//    std::cout << "Decoded text: " << decodedText << std::endl;

    TextOperations::write(decodedText, "../resources/decoded_text.txt");

    std::string decodedTextFromBinary = tree.decodeFromBinary("../resources/encoded_text.bin", root);
//    std::cout << "Decoded text from binary: " << decodedTextFromBinary << std::endl;

    auto endTime = __timeNow();
    auto elapsedTime = __milliseconds(endTime - startTime);
    std::cout << "Elapsed time: " << elapsedTime << " ms" << std::endl;
    return 0;
}