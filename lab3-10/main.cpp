#include <windows.h>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "AVL.h"
#include "BST.h"
#include "Trie.h"

template <typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

void demoAVL() {
    std::cout << "=== AVL-дерево ===\n";
    AVLTree avl;
    std::vector<int> values = {10, 20, 30, 40, 50, 25};

    for (int v : values) {
        avl.insert(v);
        std::cout << "Вставка " << v << ", максимум сейчас: " << avl.getMax() << "\n";
    }

    std::cout << "Поиск 25: " << (avl.search(25) ? "найден" : "не найден") << "\n";
    std::cout << "Поиск 99: " << (avl.search(99) ? "найден" : "не найден") << "\n";
    std::cout << "Максимальный элемент: " << avl.getMax() << "\n";
}

void demoTrie() {
    std::cout << "\n=== Trie ===\n";
    Trie trie;

    std::vector<std::string> words = {"cat", "car", "cart", "dog"};
    for (const auto& w : words) {
        trie.insert(w);
        std::cout << "Вставлено: " << w << "\n";
    }

    std::cout << "\nПоиск:\n";
    std::cout << "  cat: " << (trie.search("cat") ? "найдено" : "не найдено") << "\n";
    std::cout << "  car: " << (trie.search("car") ? "найдено" : "не найдено") << "\n";
    std::cout << "  ca:  " << (trie.search("ca") ? "найдено" : "не найдено") << " (префикс, не слово)\n";
    std::cout << "  dog: " << (trie.search("dog") ? "найдено" : "не найдено") << "\n";

    std::cout << "\nУдаляем car\n";
    trie.remove("car");
    std::cout << "  car: " << (trie.search("car") ? "найдено" : "не найдено") << "\n";
    std::cout << "  cart: " << (trie.search("cart") ? "найдено" : "не найдено") << "\n";
    std::cout << "  cat: " << (trie.search("cat") ? "найдено" : "не найдено") << "\n";
}

// Один прогон замера для заданного N и типа данных.
// Возвращает: {вставка BST, вставка AVL, поиск BST, поиск AVL}
struct BenchResult {
    long long bstInsert;
    long long avlInsert;
    long long bstSearch;
    long long avlSearch;
};

BenchResult runBenchmark(int n, const std::vector<int>& data, const std::vector<int>& queries) {
    BST bst;
    AVLTree avl;

    long long tBstIns = measureTime([&]() {
        for (int v : data) bst.insert(v);
    });
    long long tAvlIns = measureTime([&]() {
        for (int v : data) avl.insert(v);
    });

    long long tBstSrch = measureTime([&]() {
        for (int q : queries) bst.search(q);
    });
    long long tAvlSrch = measureTime([&]() {
        for (int q : queries) avl.search(q);
    });

    return {tBstIns, tAvlIns, tBstSrch, tAvlSrch};
}

void benchmark() {
    std::cout << "\n=== Сравнение BST и AVL ===\n";
    std::cout << "Время в мкс, усреднено по 5 прогонам\n";

    int sizes[] = {1000, 5000, 10000};
    const int QUERIES = 20000;
    const int RUNS = 5;

    for (int n : sizes) {
        // Подготовка данных
        std::vector<int> randomData(n);
        for (int i = 0; i < n; i++) randomData[i] = rand() % (n * 10);

        std::vector<int> sortedData(n);
        for (int i = 0; i < n; i++) sortedData[i] = i;

        std::vector<int> queries(QUERIES);
        for (int i = 0; i < QUERIES; i++) queries[i] = rand() % (n * 10);

        // Усреднение по прогонам
        BenchResult randSum{0, 0, 0, 0};
        BenchResult sortSum{0, 0, 0, 0};

        for (int r = 0; r < RUNS; r++) {
            BenchResult rr = runBenchmark(n, randomData, queries);
            randSum.bstInsert += rr.bstInsert;
            randSum.avlInsert += rr.avlInsert;
            randSum.bstSearch += rr.bstSearch;
            randSum.avlSearch += rr.avlSearch;

            BenchResult rs = runBenchmark(n, sortedData, queries);
            sortSum.bstInsert += rs.bstInsert;
            sortSum.avlInsert += rs.avlInsert;
            sortSum.bstSearch += rs.bstSearch;
            sortSum.avlSearch += rs.avlSearch;
        }

        randSum.bstInsert /= RUNS; randSum.avlInsert /= RUNS;
        randSum.bstSearch /= RUNS; randSum.avlSearch /= RUNS;
        sortSum.bstInsert /= RUNS; sortSum.avlInsert /= RUNS;
        sortSum.bstSearch /= RUNS; sortSum.avlSearch /= RUNS;

        std::cout << "\nN = " << n << ":\n";
        std::cout << "  случайные данные:\n";
        std::cout << "    вставка: BST = " << randSum.bstInsert
                  << " мкс, AVL = " << randSum.avlInsert << " мкс\n";
        std::cout << "    поиск:   BST = " << randSum.bstSearch
                  << " мкс, AVL = " << randSum.avlSearch << " мкс\n";
        std::cout << "  отсортированные данные:\n";
        std::cout << "    вставка: BST = " << sortSum.bstInsert
                  << " мкс, AVL = " << sortSum.avlInsert << " мкс\n";
        std::cout << "    поиск:   BST = " << sortSum.bstSearch
                  << " мкс, AVL = " << sortSum.avlSearch << " мкс\n";
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    srand(42); // фиксируем seed для воспроизводимости

    demoAVL();
    demoTrie();
    benchmark();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}