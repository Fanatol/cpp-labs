#include <windows.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "BinarySearch.h"
#include "HashTable.h"

// Замер времени
template <typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

// Демонстрация двоичного поиска
void demoBinarySearch() {
    std::cout << "=== Двоичный поиск ===\n";

    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int n = 7;

    std::cout << "Массив: [1, 3, 5, 7, 9, 11, 13]\n";

    std::cout << "Итеративный поиск 7: " << binSearchIte(arr, n, 7) << "\n";
    std::cout << "Итеративный поиск 1: " << binSearchIte(arr, n, 1) << "\n";
    std::cout << "Итеративный поиск 13: " << binSearchIte(arr, n, 13) << "\n";
    std::cout << "Итеративный поиск 6: " << binSearchIte(arr, n, 6) << " (не найден)\n";

    std::cout << "Рекурсивный поиск 7: " << binSearchRec(arr, 0, n - 1, 7) << "\n";
    std::cout << "Рекурсивный поиск 1: " << binSearchRec(arr, 0, n - 1, 1) << "\n";
    std::cout << "Рекурсивный поиск 13: " << binSearchRec(arr, 0, n - 1, 13) << "\n";
    std::cout << "Рекурсивный поиск 6: " << binSearchRec(arr, 0, n - 1, 6) << " (не найден)\n";
}

// Демонстрация хеш-таблицы
void demoHashTable() {
    std::cout << "\n=== Хеш-таблица (линейное пробирование) ===\n";

    HashTable<int, int> ht(10);

    std::cout << "Вставляем: (10, 100), (20, 200), (30, 300), (15, 150), (25, 250)\n";
    ht.insert(10, 100);
    ht.insert(20, 200);
    ht.insert(30, 300);
    ht.insert(15, 150);
    ht.insert(25, 250);

    int value;
    std::cout << "\nПоиск:\n";
    if (ht.find(20, value)) std::cout << "  Ключ 20 -> " << value << "\n";
    if (ht.find(15, value)) std::cout << "  Ключ 15 -> " << value << "\n";
    if (!ht.find(99, value)) std::cout << "  Ключ 99 не найден\n";

    std::cout << "\nОбновляем (20, 999)\n";
    ht.insert(20, 999);
    if (ht.find(20, value)) std::cout << "  Ключ 20 -> " << value << "\n";

    std::cout << "\nУдаляем 15\n";
    ht.remove(15);
    if (!ht.find(15, value)) {
        std::cout << "  Ключ 15 больше не найден\n";
    } else {
        std::cout << "  ОШИБКА: ключ 15 всё ещё найден\n";
    }

    std::cout << "\nВставляем 35 (коллизия с 25)\n";
    ht.insert(35, 350);
    if (ht.find(35, value)) std::cout << "  Ключ 35 -> " << value << "\n";
}

// Сравнение производительности
void benchmark() {
    std::cout << "\n=== Сравнение производительности ===\n";
    std::cout << "N\t\tbinary\t\thash\n";

    int sizes[] = {1000, 10000, 100000};
    const int QUERIES = 10000;

    for (int n : sizes) {
        int* arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = i;

        HashTable<int, int> ht(n * 2);
        for (int i = 0; i < n; i++) ht.insert(i, i);

        int* queries = new int[QUERIES];
        for (int i = 0; i < QUERIES; i++) {
            queries[i] = (i * 37 + 13) % n;
        }

        long long tBinary = measureTime([&]() {
            for (int i = 0; i < QUERIES; i++) {
                binSearchIte(arr, n, queries[i]);
            }
        });

        long long tHash = measureTime([&]() {
            int value;
            for (int i = 0; i < QUERIES; i++) {
                ht.find(queries[i], value);
            }
        });

        std::cout << n << "\t\t" << tBinary << "\t\t" << tHash << "\n";

        delete[] arr;
        delete[] queries;
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    demoBinarySearch();
    demoHashTable();
    benchmark();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}