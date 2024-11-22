//
// Created by Mustafa Mert Aladağ on 21.11.2024.
//

#ifndef __MEASUREMENTS_H__
#define __MEASUREMENTS_H__

#include <string>
#include <map>
#include <cmath>

class Measurements
{
public:
    /**
     * Calculates the compression ratio of the given strings.
     * Formula: CR = Compressed size / Uncompressed size
     * @param uncompressed Uncompressed string
     * @param compressed Compressed string
     * @return Compression ratio
     */
    static double calculateCompressionRatio(const std::string& uncompressed, const std::string& compressed)
    {
        return (double)compressed.size() / uncompressed.size();
    }

    /**
     * Calculates the saved space percentage of the given strings.
     * Formula: SS = 1 - Compression ratio
     * @param uncompressed Uncompressed string
     * @param compressed Compressed string
     * @return Saved space percentage
     */
    static double calculateSavedSpace(const std::string& uncompressed, const std::string& compressed)
    {
        return 1 - calculateCompressionRatio(uncompressed, compressed);
    }

    /**
     * Calculates the Shannon entropy of the given frequency map.
     * Formula: H(U) = -Σ(p(x) * log2(p(x)))
     * @param frequencyMap Frequency map of the characters
     * @param textSize Size of the text
     * @return Entropy of the text
     */
    static double calculateEntropy(std::map<char, int> frequencyMap, int textSize)
    {
        double entropy = 0;
        for (auto p : frequencyMap)
        {
            double probability = (double)p.second / textSize;
            entropy += probability * log2(probability);
        }
        return -entropy;
    }

    /**
     * Calculates the average code length of the given frequency map and Huffman codes.
     * Formula: L = Σ(p(x) * l(x))
     * @param frequencyMap Frequency map of the characters
     * @param huffmanCodes Huffman codes of the characters
     * @return Average code length
     */
    static double calculateAverageCodeLength(std::map<char, int> frequencyMap, const std::map<char, std::string>& huffmanCodes)
    {
        int textSize = 0;
        double totalCodeLength = 0;
        for (auto p : frequencyMap)
        {
            textSize += p.second;
            totalCodeLength += p.second * huffmanCodes.at(p.first).size();
        }
        return totalCodeLength / textSize;
    }

    /**
     * Calculates the redundancy of the given frequency map.
     * Formula: R = 1 - (H(U) / max(H(U))
     * @param frequencyMap Frequency map of the characters
     * @param textSize Size of the text
     * @return Redundancy of the text
     */
    static double calculateRedundancy(std::map<char, int> frequencyMap, int textSize)
    {
        double entropy = calculateEntropy(frequencyMap, textSize);
        double maxEntropy = log2(frequencyMap.size());
        return 1 - (entropy / maxEntropy);
    }

};

#endif //__MEASUREMENTS_H__
