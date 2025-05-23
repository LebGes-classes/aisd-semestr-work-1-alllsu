// HuffmanTree.h
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

class HuffmanTree {
private:
    class Node {
    public:
        char ch;
        int freq;
        Node* left;
        Node* right;
        Node(char c, int f);
        Node(int f, Node* l, Node* r);
    };

    class Compare {
    public:
        bool operator()(Node* l, Node* r);
    };

    Node* root;
    std::unordered_map<char, std::string> codes;
    std::string characters;
    std::vector<int> frequencies;

    void generateCodes(Node* node, std::string code);
    void deleteTree(Node* node);
    void rebuildTree();

public:
    HuffmanTree();
    ~HuffmanTree();
    void buildTree(const std::string& s, const std::vector<int>& freq);
    void addCharacter(char c, int freq);
    void removeCharacter(char c);
    std::vector<std::string> getCodes() const;
    void printCodes();
};