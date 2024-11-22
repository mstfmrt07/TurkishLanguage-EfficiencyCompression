//
// Created by Mustafa Mert Aladağ on 18.11.2024.
//

#include <map>
#include <iostream>

#include "Utils.h"
#include "Node.h"
#include "HuffmanTree.h"
#include "TextOperations.h"
#include "Measurements.h"

std::map<char, int> getFrequencyMap(const std::string &str)
{
    std::map<char, int> frequencyMap;
    for (char c: str)
    {
        frequencyMap[c]++;
    }

    return frequencyMap;
}

void saveFrequencyMapToText(std::string filteredStr)
{

    // Write frequencies to a text file
    std::wstring filteredStrWstr = TextOperations::utf8_to_wstring(filteredStr);

    std::wstring frequenciesStr;
    std::map<wchar_t, int> frequenciesMap;
    for (const auto& wch : filteredStrWstr)
    {
        frequenciesMap[wch]++;
    }

    for (const auto& [key, value] : frequenciesMap)
    {
        frequenciesStr += key;
        frequenciesStr += L": ";
        frequenciesStr += std::to_wstring(value);
        frequenciesStr += L"\n";
    }

    std::string frequenciesUtf8 = TextOperations::wstring_to_utf8(frequenciesStr);

    TextOperations::write(frequenciesUtf8, "../resources/frequencies.txt");
}

void saveLookupTableToText(std::map<char, std::string> codes)
{
    std::string lookupTable;
    for (const auto& [key, value] : codes)
    {
        lookupTable += key;
        lookupTable += ": ";
        lookupTable += value;
        lookupTable += "\n";
    }

    TextOperations::write(lookupTable, "../resources/lookup_table.txt");
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
//    std::cout << "Encoded text: " << encodedText << std::endl;

//    TextOperations::write(encodedText, "../resources/encoded_text.txt");

    tree.encodeToBinary(filteredStr, codes, "../resources/encoded_text.txt");

    std::string decodedTextFromBinary = tree.decodeFromBinary("../resources/encoded_text.txt", root);

    TextOperations::write(decodedTextFromBinary, "../resources/decoded_text.txt");
//    std::cout << "Decoded text from binary: " << decodedTextFromBinary << std::endl;

    // Save frequencies to a text file
     saveFrequencyMapToText(filteredStr);

     // Save lookup table to a text file
    saveLookupTableToText(codes);

    // Print measurements
    std::string measurementsText;

    std::ifstream encodedFile("../resources/encoded_text.txt", std::ios::binary);
    std::string encodedText((std::istreambuf_iterator<char>(encodedFile)), std::istreambuf_iterator<char>());

    double compressionRatio = Measurements::calculateCompressionRatio(filteredStr, encodedText);
    measurementsText += "Compression ratio: " + std::to_string(compressionRatio) + "\n";

    double savedSpace = Measurements::calculateSavedSpace(filteredStr, encodedText);
    measurementsText += "Saved space: " + std::to_string(savedSpace) + "\n";

    double entropy = Measurements::calculateEntropy(frequencies, filteredStr.size());
    measurementsText += "Entropy: " + std::to_string(entropy) + "\n";

    double averageCodeLength = Measurements::calculateAverageCodeLength(frequencies, codes);
    measurementsText += "Average code length: " + std::to_string(averageCodeLength) + "\n";

    double redundancy = Measurements::calculateRedundancy(frequencies, filteredStr.size());
    measurementsText += "Redundancy: " + std::to_string(redundancy) + "\n";

    TextOperations::write(measurementsText, "../resources/measurements.txt");

    auto endTime = __timeNow();
    auto elapsedTime = __milliseconds(endTime - startTime);
    std::cout << "Elapsed time: " << elapsedTime << " ms" << std::endl;
    return 0;
}