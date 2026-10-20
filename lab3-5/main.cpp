#include <windows.h>

#include <iostream>
#include <string>

#include "Deque.h"
#include "PriorityQueue.h"
#include "Queue.h"
#include "Stack.h"

// ============================================================
// Демонстрация Stack + evaluateRPN
// ============================================================
void demoStack() {
    std::cout << "\n=== Демонстрация Stack ===\n";

    Stack<int> s;
    std::cout << "\n--- Пустой стек ---\n";
    std::cout << "isEmpty = " << (s.isEmpty() ? "да" : "нет") << ", size = " << s.size() << "\n";

    std::cout << "\n--- push(10), push(20), push(30) ---\n";
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "size = " << s.size() << ", top = " << s.top() << "\n";

    std::cout << "\n--- pop() ---\n";
    std::cout << "pop = " << s.pop() << "\n";
    std::cout << "После pop: size = " << s.size() << ", top = " << s.top() << "\n";

    std::cout << "\n--- Обработка ошибок: pop из пустого ---\n";
    try {
        Stack<int> empty;
        empty.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "Поймано: " << e.what() << "\n";
    }

    std::cout << "\n--- evaluateRPN ---\n";
    std::cout << "3 4 +       = " << evaluateRPN("3 4 +") << "\n";
    std::cout << "3 4 + 5 *   = " << evaluateRPN("3 4 + 5 *") << "\n";
    std::cout << "5 1 2 + 4 * + 3 - = " << evaluateRPN("5 1 2 + 4 * + 3 -") << "\n";
    std::cout << "10 2 /      = " << evaluateRPN("10 2 /") << "\n";

    std::cout << "\n--- Ошибки evaluateRPN ---\n";
    try {
        evaluateRPN("3 +");
    } catch (const std::exception& e) {
        std::cout << "\"3 +\" — " << e.what() << "\n";
    }
    try {
        evaluateRPN("10 0 /");
    } catch (const std::exception& e) {
        std::cout << "\"10 0 /\" — " << e.what() << "\n";
    }
}

// ============================================================
// Демонстрация Queue (на двух стеках)
// ============================================================
void demoQueue() {
    std::cout << "\n\n=== Демонстрация Queue ===\n";

    Queue<int> q;
    std::cout << "\n--- Пустая очередь ---\n";
    std::cout << "isEmpty = " << (q.isEmpty() ? "да" : "нет") << ", size = " << q.size() << "\n";

    std::cout << "\n--- enqueue(1), enqueue(2), enqueue(3) ---\n";
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    std::cout << "size = " << q.size() << ", front = " << q.front() << "\n";

    std::cout << "\n--- dequeue() ---\n";
    std::cout << "dequeue = " << q.dequeue() << "\n";
    std::cout << "После dequeue: front = " << q.front() << ", size = " << q.size() << "\n";

    std::cout << "\n--- Перекладывание между стеками ---\n";
    q.dequeue();
    q.enqueue(4);
    q.enqueue(5);
    std::cout << "size = " << q.size() << ", front = " << q.front() << "\n";
    std::cout << "dequeue = " << q.dequeue() << "\n";
    std::cout << "dequeue = " << q.dequeue() << "\n";
    std::cout << "dequeue = " << q.dequeue() << "\n";

    std::cout << "\n--- Обработка ошибок: dequeue из пустой ---\n";
    try {
        q.dequeue();
    } catch (const std::underflow_error& e) {
        std::cout << "Поймано: " << e.what() << "\n";
    }
}

// ============================================================
// Демонстрация Deque (кольцевой буфер)
// ============================================================
void demoDeque() {
    std::cout << "\n\n=== Демонстрация Deque ===\n";

    Deque<int> d;
    std::cout << "\n--- Пустой дек ---\n";
    std::cout << "isEmpty = " << (d.isEmpty() ? "да" : "нет") << ", size = " << d.size() << "\n";

    std::cout << "\n--- push_back(10), push_back(20) ---\n";
    d.push_back(10);
    d.push_back(20);
    std::cout << "size = " << d.size() << ", front = " << d.front() << ", back = " << d.back()
              << "\n";

    std::cout << "\n--- push_front(5), push_front(1) ---\n";
    d.push_front(5);
    d.push_front(1);
    std::cout << "size = " << d.size() << ", front = " << d.front() << ", back = " << d.back()
              << "\n";

    std::cout << "\n--- pop_front(), pop_back() ---\n";
    std::cout << "pop_front = " << d.pop_front() << "\n";
    std::cout << "pop_back  = " << d.pop_back() << "\n";
    std::cout << "После: front = " << d.front() << ", back = " << d.back()
              << ", size = " << d.size() << "\n";

    std::cout << "\n--- Демонстрация кольцевого буфера ---\n";
    Deque<int> ring(4);  // фиксированная ёмкость 4
    ring.push_back(1);
    ring.push_back(2);
    ring.push_back(3);
    ring.push_back(4);
    std::cout << "Заполнили 4 элемента: size = " << ring.size() << ", front = " << ring.front()
              << ", back = " << ring.back() << "\n";

    ring.pop_front();
    ring.pop_front();
    ring.push_back(5);
    ring.push_back(6);
    std::cout << "После pop_front x2 и push_back(5,6): size = " << ring.size()
              << ", front = " << ring.front() << ", back = " << ring.back() << "\n";
    std::cout << "(индексы завернулись через конец массива, но дек работает)\n";

    std::cout << "\n--- Обработка ошибок: pop из пустого ---\n";
    try {
        Deque<int> empty;
        empty.pop_front();
    } catch (const std::underflow_error& e) {
        std::cout << "Поймано: " << e.what() << "\n";
    }
}

// ============================================================
// Демонстрация PriorityQueue + findKSmallest
// ============================================================
void demoPriorityQueue() {
    std::cout << "\n\n=== Демонстрация PriorityQueue ===\n";

    PriorityQueue<int> pq;
    std::cout << "\n--- Пустая очередь ---\n";
    std::cout << "isEmpty = " << (pq.isEmpty() ? "да" : "нет") << ", size = " << pq.size() << "\n";

    std::cout << "\n--- push(30, 10, 50, 20) ---\n";
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);
    std::cout << "size = " << pq.size() << ", top = " << pq.top() << "\n";

    std::cout << "\n--- pop() — элементы по убыванию ---\n";
    while (!pq.isEmpty()) {
        std::cout << pq.pop() << " ";
    }
    std::cout << "\n";

    std::cout << "\n--- Обработка ошибок: pop из пустой ---\n";
    try {
        pq.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "Поймано: " << e.what() << "\n";
    }

    std::cout << "\n--- findKSmallest ---\n";
    int arr[] = {7, 2, 9, 4, 1, 8, 3};
    int n = 7;
    std::cout << "Массив: 7 2 9 4 1 8 3\n";
    std::cout << "K = 3, наименьшие (по убыванию): ";
    findKSmallest(arr, n, 3);
    std::cout << "\n";
}

// ============================================================
// main
// ============================================================
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    demoStack();
    demoQueue();
    demoDeque();
    demoPriorityQueue();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}