// HuffmanTree.cpp
#include "HuffmanTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// Реализация методов класса Node
HuffmanTree::Node::Node(char c, int f) {
    ch = c;
    freq = f;
    left = nullptr;
    right = nullptr;
}

HuffmanTree::Node::Node(int f, Node* l, Node* r) {
    ch = '\0';
    freq = f;
    left = l;
    right = r;
}

// Реализация класса Compare
bool HuffmanTree::Compare::operator()(Node* l, Node* r) {
    return l->freq > r->freq;
}

// Генерация двоичных кодов
void HuffmanTree::generateCodes(Node* node, string code) {
    // Если встретился лист
    if (!node->left && !node->right) {
        codes[node->ch] = code;
        return;
    }

    // Для всех остальных вершин
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

// Удаление дерева
void HuffmanTree::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Перестроение дерева
void HuffmanTree::rebuildTree() {
    // Очищаем текущее дерево
    deleteTree(root);
    root = nullptr;
    codes.clear();

    if (characters.empty()) return;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Создаём листья
    for (size_t i = 0; i < characters.length(); ++i) {
        pq.push(new Node(characters[i], frequencies[i]));
    }

    // Строим дерево
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(left->freq + right->freq, left, right);
        pq.push(parent);
    }

    root = pq.top();
    generateCodes(root, "");
}

// Конструктор
HuffmanTree::HuffmanTree() {
    root = nullptr;
}

// Деструктор
HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}

// Построение дерева
void HuffmanTree::buildTree(const string& s, const vector<int>& freq) {
    characters = s;
    frequencies = freq;
    rebuildTree();
}

// Добавление нового символа
void HuffmanTree::addCharacter(char c, int freq) {
    characters += c;
    frequencies.push_back(freq);
    rebuildTree();
}

// Удаление символа
void HuffmanTree::removeCharacter(char c) {
    size_t pos = characters.find(c);
    if (pos != string::npos) {
        characters.erase(pos, 1);
        frequencies.erase(frequencies.begin() + pos);
        rebuildTree();
    }
}

// Получение кодов
vector<string> HuffmanTree::getCodes() const {
    vector<string> result;
    for (const auto& pair : codes) {
        result.push_back(string(1, pair.first) + ": " + pair.second);
    }
    return result;
}

// Вывод кодов
void HuffmanTree::printCodes() {
    for (const auto& pair : codes) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
}