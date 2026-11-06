#include <algorithm>
#include <iostream>

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const int& value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
   private:
    BSTNode* root;

    // Часть 1: обходы и характеристики

    void preOrder(BSTNode* node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(BSTNode* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(BSTNode* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << " ";
    }

    int countLeaves(BSTNode* node) {
        if (node == nullptr) return 0;
        if (node->left == nullptr and node->right == nullptr) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    // Удаление дерева (post-order)
    void destroy(BSTNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    // Часть 2: операции BST

    BSTNode* insert(BSTNode* node, int key) {
        if (node == nullptr) return new BSTNode(key);
        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        return node;
    }

    BSTNode* search(BSTNode* node, int key) {
        if (node == nullptr) return nullptr;
        if (node->data == key) return node;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }

    // Удаление узла (три случая)
    BSTNode* remove(BSTNode* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->data)
            node->left = remove(node->left, key);
        else if (key > node->data)
            node->right = remove(node->right, key);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            } else {
                BSTNode* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    BSTNode* findMax(BSTNode* node) {
        while (node->right != nullptr) node = node->right;
        return node;
    }

    int height(BSTNode* node) {
        if (node == nullptr)
            return 0;
        else
            return 1 + std::max(height(node->left), height(node->right));
    }

    // Поиск k-го наименьшего (in-order со счётчиком)
    int findKthSmallest(BSTNode* node, int k, int& count) {
        if (node == nullptr) return -1;
        int left = findKthSmallest(node->left, k, count);
        if (left != -1) return left;
        count++;
        if (count == k) return node->data;
        return findKthSmallest(node->right, k, count);
    }

    void printTree(BSTNode* node, int level) {
        if (node == nullptr) return;
        std::cout << node->data << " (уровень " << level << ")\n";
        printTree(node->left, level + 1);
        printTree(node->right, level + 1);
    }

   public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); };

    // Часть 1

    void preOrder() {
        preOrder(root);
        std::cout << std::endl;
    }
    void inOrder() {
        inOrder(root);
        std::cout << std::endl;
    }
    void postOrder() {
        postOrder(root);
        std::cout << std::endl;
    }

    int countLeaves() {
        int result = countLeaves(root);
        return result;
    }

    // Часть 2

    void insert(int key) { root = insert(root, key); }

    bool search(int key) { return search(root, key) != nullptr; }

    void remove(int key) { root = remove(root, key); }

    int findKthSmallest(int k) {
        int count = 0;
        return findKthSmallest(root, k, count);
    }

    int getMin() {
        if (root == nullptr) return -1;
        BSTNode* minNode = findMin(root);
        return minNode->data;
    }

    int getMax() {
        if (root == nullptr) return -1;
        BSTNode* maxNode = findMax(root);
        return maxNode->data;
    }

    int height() { return height(root); }

    void printTree() { printTree(root, 0); }
};