//
// Created by Mustafa Mert Aladağ on 19.11.2024.
//

#ifndef __HUFFMANTREE_H__
#define __HUFFMANTREE_H__

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <bitset>
#include <fstream>

#include "Node.h"

#define NUM_BITS 8

class HuffmanTree
{
public:
    HuffmanTree(const std::map<char, int>& frequencyMap)
    {
        this->m_frequencyMap = frequencyMap;
        this->m_rootNode = buildHuffmanTree();
    }

    ~HuffmanTree()
    {
        delete m_rootNode;
    }

    /**
     * Generates Huffman codes for each character in the tree recursively.
     * @param node Root node of the Huffman tree
     * @param code Initial code (empty string)
     * @param codes Map to store the generated codes
     */
    void generateCodes(Node* node, std::string code, std::map<char, std::string>& codes)
    {
        // Leaf node
        if (node->left == nullptr && node->right == nullptr)
        {
            codes[node->data] = code;
            return;
        }
        generateCodes(node->left, code + "0", codes);
        generateCodes(node->right, code + "1", codes);
    }

    std::string encodeToString(const std::string& text, const std::map<char, std::string>& huffmanCodes)
    {
        std::string encodedText;
        for (char ch : text)
        {
            encodedText += huffmanCodes.at(ch);
        }
        return encodedText;
    }

    void encodeToBinary(const std::string& text,
                        const std::map<char, std::string>& huffmanCodes,
                        const std::string& filename)
    {

        std::ofstream outputFile(filename, std::ios::binary);
        if (!outputFile.is_open())
        {
            std::cerr << "Error while opening file for encoding." << std::endl;
            return;
        }

        std::string encodedText = encodeToString(text, huffmanCodes);

        int padding = NUM_BITS - (encodedText.length() % NUM_BITS);
        if (padding != NUM_BITS)
        {
            encodedText += std::string(padding, '0');
        }

        // Put padding info (first byte)
        outputFile.put(static_cast<char>(padding));

        for (size_t i = 0; i < encodedText.length(); i += NUM_BITS)
        {
            std::bitset<NUM_BITS> bits(encodedText.substr(i, NUM_BITS));
            char byte = static_cast<char>(bits.to_ulong());
            outputFile.put(byte);
        }

        outputFile.close();
    }

    std::string decodeFromString(const std::string& encodedText, Node* root)
    {
        std::string decodedText;
        Node* current = root;
        for (char bit : encodedText)
        {
            if (bit == '0')
            {
                current = current->left;
            }
            else if (bit == '1')
            {
                current = current->right;
            }

            // Leaf node
            if (current->left == nullptr && current->right == nullptr)
            {
                decodedText += current->data;
                current = root;
            }
        }
        return decodedText;
    }

    std::string decodeFromBinary(const std::string& filename, Node* root)
    {
        std::ifstream inputFile(filename, std::ios::binary);
        if (!inputFile.is_open())
        {
            std::cerr << "Error while opening file for decoding." << std::endl;
            return "";
        }

        // Get the padding information (first byte)
        char paddingChar;
        inputFile.get(paddingChar);
        int padding = static_cast<int>(paddingChar);

        std::string encodedText;
        char byte;
        while (inputFile.get(byte))
        {
            std::bitset<NUM_BITS> bits(byte);
            encodedText += bits.to_string();
        }

        inputFile.close();

        // Remove padding from the encoded text
        encodedText.erase(encodedText.length() - padding);

        return decodeFromString(encodedText, root);
    }


    Node* getRootNode()
    {
        return m_rootNode;
    }

private:
    std::map<char, int> m_frequencyMap;
    Node* m_rootNode;

    /**
     * Build the Huffman tree using priority queue.
     * Algorithm:
     * 1. Create a leaf node for each symbol and add it to the priority queue.
     * 2. While there is more than one node in the queue:
     *      1. Remove the two nodes of highest priority (lowest probability) from the queue
     *      2. Create a new internal node with these two nodes as children and with probability equal to the sum of the two nodes' probabilities.
     *      3. Add the new node to the queue.
     * 3. The remaining node is the root node and the tree is complete.
     * @return Root node of the Huffman tree
     * @see https://en.wikipedia.org/wiki/Huffman_coding
     */
    Node* buildHuffmanTree()
    {
        std::priority_queue<Node*, std::vector<Node*>, NodeComparator> tree;
        for (const auto& pair : m_frequencyMap)
        {
            tree.push(new Node(pair.first, pair.second));
        }

        while (tree.size() > 1)
        {
            Node* left = tree.top();
            tree.pop();

            Node* right = tree.top();
            tree.pop();

            Node* parent = new Node('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            tree.push(parent);
        }

        return tree.top();
    }

};

#endif //__HUFFMANTREE_H__
