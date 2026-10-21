#include <windows.h>

#include <chrono>
#include <iostream>

#include "Recursion.h"
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
// Печать массива
// ============================================================
void printArray(const int arr[], int n) {
    std::cout << "[";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

// ============================================================
// Демонстрация рекурсии
// ============================================================
void demoRecursion() {
    std::cout << "=== Демонстрация рекурсии ===\n";

    std::cout << "\n--- Факториал ---\n";
    for (int n = 0; n <= 7; n++) {
        std::cout << n << "! = " << factorial(n) << "\n";
    }

    std::cout << "\n--- Числа Фибоначчи ---\n";
    for (int n = 0; n <= 10; n++) {
        std::cout << "fib(" << n << ") = " << fib(n) << "\n";
    }

    std::cout << "\n--- Количество цифр ---\n";
    std::cout << "countDigits(0) = " << countDigits(0) << "\n";
    std::cout << "countDigits(7) = " << countDigits(7) << "\n";
    std::cout << "countDigits(42) = " << countDigits(42) << "\n";
    std::cout << "countDigits(12345) = " << countDigits(12345) << "\n";
    std::cout << "countDigits(-987) = " << countDigits(-987) << "\n";

    std::cout << "\n--- Бинарный поиск ---\n";
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int n = 7;
    std::cout << "Массив: ";
    printArray(arr, n);
    std::cout << "Поиск 7  → индекс " << binarySearch(arr, 0, n - 1, 7) << "\n";
    std::cout << "Поиск 1  → индекс " << binarySearch(arr, 0, n - 1, 1) << "\n";
    std::cout << "Поиск 13 → индекс " << binarySearch(arr, 0, n - 1, 13) << "\n";
    std::cout << "Поиск 6  → индекс " << binarySearch(arr, 0, n - 1, 6) << " (не найден)\n";
}

// ============================================================
// Демонстрация сортировок
// ============================================================
void demoSorts() {
    std::cout << "\n\n=== Демонстрация сортировок ===\n";

    int base[] = {5, 2, 4, 6, 1, 3};
    int n = 6;

    int a[6], b[6], c[6];
    for (int i = 0; i < n; i++) {
        a[i] = base[i];
        b[i] = base[i];
        c[i] = base[i];
    }

    std::cout << "\nИсходный массив: ";
    printArray(base, n);

    std::cout << "\n--- Пузырьковая ---\n";
    std::cout << "До:    ";
    printArray(a, n);
    bubbleSort(a, n);
    std::cout << "После: ";
    printArray(a, n);

    std::cout << "\n--- Вставками ---\n";
    std::cout << "До:    ";
    printArray(b, n);
    insertionSort(b, n);
    std::cout << "После: ";
    printArray(b, n);

    std::cout << "\n--- Выбором ---\n";
    std::cout << "До:    ";
    printArray(c, n);
    selectionSort(c, n);
    std::cout << "После: ";
    printArray(c, n);
}

void benchmark() {
    std::cout << "\n\n=== Сравнение производительности (почти отсортированный массив) ===\n";
    std::cout << "N\t\tbubble\t\tinsertion\tselection\n";

    int sizes[] = {1000, 5000, 10000, 50000};

    for (int n : sizes) {
        int* arr = new int[n];

        // Заполняем почти отсортированным: 0..n-1, потом меняем 3 пары
        for (int i = 0; i < n; i++) arr[i] = i;
        std::swap(arr[0], arr[1]);
        std::swap(arr[n / 2], arr[n / 2 + 1]);
        std::swap(arr[n - 2], arr[n - 1]);

        long long t1 = measureTime([&]() { bubbleSort(arr, n); });

        // Восстановить
        for (int i = 0; i < n; i++) arr[i] = i;
        std::swap(arr[0], arr[1]);
        std::swap(arr[n / 2], arr[n / 2 + 1]);
        std::swap(arr[n - 2], arr[n - 1]);

        long long t2 = measureTime([&]() { insertionSort(arr, n); });

        // Восстановить
        for (int i = 0; i < n; i++) arr[i] = i;
        std::swap(arr[0], arr[1]);
        std::swap(arr[n / 2], arr[n / 2 + 1]);
        std::swap(arr[n - 2], arr[n - 1]);

        long long t3 = measureTime([&]() { selectionSort(arr, n); });

        std::cout << n << "\t\t" << t1 << "\t\t" << t2 << "\t\t" << t3 << "\n";

        delete[] arr;
    }
}

// ============================================================
// main
// ============================================================
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    demoRecursion();
    demoSorts();
    benchmark();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}