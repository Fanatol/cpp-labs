#include <algorithm>
#include <iostream>
#include <stdexcept>

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
   private:
    AVLNode* root;

    int height(AVLNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int balanceFactor(AVLNode* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(AVLNode* node) {
        if (node == nullptr) return;
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    // Правый поворот
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Левый поворот
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Вставка с балансировкой
    AVLNode* insert(AVLNode* node, int key) {
        if (node == nullptr)
            return new AVLNode(key);
        else if (node->key > key)
            node->left = insert(node->left, key);
        else if (node->key < key)
            node->right = insert(node->right, key);
        else
            return node;
        updateHeight(node);
        int balanceStatus = balanceFactor(node);
        if (balanceStatus > 1) {
            if (balanceFactor(node->left) >= 0) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceStatus < -1) {
            if (balanceFactor(node->right) <= 0) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        } else {
            return node;
        }
    }

    AVLNode* findMax(AVLNode* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void destroy(AVLNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    bool search(AVLNode* node, int key) {
        if (node == nullptr) return false;
        if (node->key == key)
            return true;
        else if (node->key > key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

   public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }
    void insert(int key) { root = insert(root, key); }
    int getMax() {
        if (root == nullptr) throw std::runtime_error("Дерево пустое!");
        return findMax(root)->key;
    }
    bool search(int key) { return search(root, key); }
};