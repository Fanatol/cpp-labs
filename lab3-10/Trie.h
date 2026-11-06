#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    TrieNode() : children(), isEndOfWord(false) {}
};

class Trie {
   private:
    TrieNode* root;

    void destroy(TrieNode* node) {
        if (node == nullptr) return;
        for (size_t i = 0; i < 26; i++) {
            destroy(node->children[i]);
        }
        delete node;
    }

    bool checkChildren(TrieNode* node) {
        for (TrieNode* children : node->children) {
            if (children != nullptr) return true;
        }
        return false;
    }

    // Удаление последнего узла слова
    TrieNode* delNode(TrieNode* node) {
        if (!node->isEndOfWord) {
            return node;
        } else if (checkChildren(node)) {
            node->isEndOfWord = false;
            return node;
        } else {
            delete node;
            return nullptr;
        }
    }

    // Рекурсивное удаление с очисткой пустых узлов
    TrieNode* remove(TrieNode* node, const std::string& word, int depth) {
        if (node == nullptr) return nullptr;
        if (depth == word.length()) {
            return delNode(node);
        } else {
            char ch = word[depth];
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return node;
            } else {
                node->children[index] = remove(node->children[index], word, depth + 1);
                if (!checkChildren(node) and !node->isEndOfWord) {
                    return nullptr;
                } else {
                    return node;
                }
            }
        }
    }

   public:
    Trie() : root(new TrieNode) {}
    ~Trie() { destroy(root); }

    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) current->children[index] = new TrieNode();
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == nullptr)
                return false;
            else
                current = current->children[index];
        }
        return current->isEndOfWord;
    }

    void remove(const std::string& word) { root = remove(root, word, 0); }
};