#include <windows.h>

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ExternalSort.h"
#include "Sorts.h"

// ============================================================
// Замер времени
// ============================================================
template <typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

// ============================================================
// Замеры производительности трёх сортировок
// ============================================================
void benchmark() {
    std::cout << "\n=== Сравнение производительности ===\n";
    std::cout << "N\t\tquick\t\tmerge\t\theap\n";

    int sizes[] = {1000, 5000, 10000, 50000};

    for (int n : sizes) {
        int* original = new int[n];
        for (int i = 0; i < n; i++) {
            original[i] = (i * 37 + 13) % n;
        }

        int* arrQuick = new int[n];
        int* arrMerge = new int[n];
        int* arrHeap = new int[n];
        for (int i = 0; i < n; i++) {
            arrQuick[i] = original[i];
            arrMerge[i] = original[i];
            arrHeap[i] = original[i];
        }

        long long tQuick = measureTime([&]() { quickSort(arrQuick, 0, n - 1); });
        long long tMerge = measureTime([&]() { mergeSort(arrMerge, 0, n - 1); });
        long long tHeap = measureTime([&]() { heapSort(arrHeap, n); });

        std::cout << n << "\t\t" << tQuick << "\t\t" << tMerge << "\t\t" << tHeap << "\n";

        delete[] original;
        delete[] arrQuick;
        delete[] arrMerge;
        delete[] arrHeap;
    }
}

// ============================================================
// Создание тестового файла
// ============================================================
void createTestFile(const std::string& filename, int count) {
    std::ofstream out(filename);
    for (int i = 0; i < count; i++) {
        out << (i * 37 + 13) % 100 << " ";
    }
    out.close();
}

// ============================================================
// Чтение файла и вывод
// ============================================================
void readAndPrintFile(const std::string& filename) {
    std::ifstream in(filename);
    int x;
    std::cout << "[";
    bool first = true;
    while (in >> x) {
        if (!first) std::cout << ", ";
        std::cout << x;
        first = false;
    }
    std::cout << "]\n";
    in.close();
}

// ============================================================
// Демонстрация внешней сортировки
// ============================================================
void demoExternal() {
    std::cout << "\n=== Внешняя сортировка (файлы) ===\n";

    createTestFile("input.txt", 20);

    std::cout << "Входной файл:  ";
    readAndPrintFile("input.txt");

    externalMergeSort("input.txt", "output.txt", 5);

    std::cout << "Выходной файл: ";
    readAndPrintFile("output.txt");

    std::remove("input.txt");
    std::remove("output.txt");
}

// ============================================================
// main
// ============================================================
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    benchmark();
    demoExternal();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}