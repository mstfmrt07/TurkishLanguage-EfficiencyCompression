//
// Created by Mustafa Mert Aladağ on 19.11.2024.
//

#ifndef __NODE_H__
#define __NODE_H__

/**
 * Node structure for the Huffman tree
 */
struct Node
{
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr)
    {

    }
};

/**
 * Custom comparator for the priority queue (min heap)
 */
struct NodeComparator
{
    bool operator()(Node* lhs, Node* rhs)
    {
        return lhs->freq > rhs->freq;
    }
};


#endif //__NODE_H__
