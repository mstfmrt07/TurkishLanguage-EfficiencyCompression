//
// Created by Mustafa Mert Aladağ on 19.11.2024.
//

#ifndef __HUFFMANTREE_H__
#define __HUFFMANTREE_H__

#include <iostream>
#include <vector>
#include <queue>

#include "Utils.h"
#include "Node.h"

class HuffmanTree
{
public:
    HuffmanTree(const std::unordered_map<char, int>& frequencyMap)
    {
        this->m_frequencyMap = frequencyMap;
        this->m_rootNode = buildHuffmanTree();

        std::cout << "Elapsed milliseconds for building the tree: \n" << benchmark(TimeUnit::MILLISECONDS, [&]()
        {
            m_rootNode = buildHuffmanTree();
        }) << "\n";

    }

    Node* getRootNode()
    {
        return m_rootNode;
    }

private:
    std::unordered_map<char, int> m_frequencyMap;
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
