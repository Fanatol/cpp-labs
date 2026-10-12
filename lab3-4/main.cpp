#include <windows.h>

#include <iostream>
#include <string>

#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"

// ============================================================
// Демонстрация SinglyLinkedList
// ============================================================
void demoSingly() {
    std::cout << "=== Демонстрация SinglyLinkedList ===\n";

    SinglyLinkedList<int> list;
    std::cout << "\n--- Пустой список ---\n";
    std::cout << "size = " << list.size() << ", empty = " << (list.empty() ? "да" : "нет") << "\n";
    list.print();

    std::cout << "\n--- push_back(10, 20, 30) ---\n";
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.print();
    std::cout << "size = " << list.size() << "\n";

    std::cout << "\n--- push_front(5) ---\n";
    list.push_front(5);
    list.print();
    std::cout << "size = " << list.size() << "\n";

    std::cout << "\n--- find(20) и find(99) ---\n";
    auto found = list.find(20);
    if (found != nullptr) {
        std::cout << "Найден узел со значением " << found->data << "\n";
    } else {
        std::cout << "20 не найден\n";
    }
    auto notFound = list.find(99);
    if (notFound == nullptr) {
        std::cout << "99 не найден (вернулся nullptr)\n";
    }

    std::cout << "\n--- remove(20) и remove(99) ---\n";
    std::cout << "remove(20): " << (list.remove(20) ? "удалён" : "не найден") << "\n";
    std::cout << "remove(99): " << (list.remove(99) ? "удалён" : "не найден") << "\n";
    list.print();

    std::cout << "\n--- pop_front() и pop_back() ---\n";
    list.pop_front();
    list.pop_back();
    list.print();
    std::cout << "size = " << list.size() << "\n";

    std::cout << "\n--- Обход через итератор ---\n";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "\n--- Range-based for ---\n";
    for (int x : list) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "\n--- Сравнение списков (operator==) ---\n";
    SinglyLinkedList<int> a;
    a.push_back(1);
    a.push_back(2);
    SinglyLinkedList<int> b;
    b.push_back(1);
    b.push_back(2);
    SinglyLinkedList<int> c;
    c.push_back(1);
    c.push_back(3);

    std::cout << "a == b? " << (a == b ? "да" : "нет") << "\n";
    std::cout << "a == c? " << (a == c ? "да" : "нет") << "\n";
    std::cout << "a != c? " << (a != c ? "да" : "нет") << "\n";

    std::cout << "\n--- clear() ---\n";
    list.clear();
    std::cout << "size = " << list.size() << ", empty = " << (list.empty() ? "да" : "нет") << "\n";
    list.print();

    std::cout << "\n--- Шаблон со строками ---\n";
    SinglyLinkedList<std::string> words;
    words.push_back("мир");
    words.push_back("труд");
    words.push_front("Привет");
    words.print();
}

// ============================================================
// Демонстрация DoublyLinkedList
// ============================================================
void demoDoubly() {
    std::cout << "\n\n=== Демонстрация DoublyLinkedList ===\n";

    DoublyLinkedList<int> list;
    std::cout << "\n--- Пустой список ---\n";
    std::cout << "size = " << list.size() << ", empty = " << (list.empty() ? "да" : "нет") << "\n";
    list.print();
    list.printReverse();

    std::cout << "\n--- push_back(10, 20, 30, 40) ---\n";
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.print();
    std::cout << "size = " << list.size() << "\n";

    std::cout << "\n--- push_front(5) ---\n";
    list.push_front(5);
    list.print();

    std::cout << "\n--- printReverse() ---\n";
    list.printReverse();

    std::cout << "\n--- find(30) + insert_after ---\n";
    auto node30 = list.find(30);
    if (node30 != nullptr) {
        list.insert_after(node30, 35);
        std::cout << "Вставлено 35 после 30\n";
    }
    list.print();

    std::cout << "\n--- find(20) + erase по указателю ---\n";
    auto node20 = list.find(20);
    if (node20 != nullptr) {
        list.erase(node20);
        std::cout << "Удалён узел со значением 20\n";
    }
    list.print();
    std::cout << "size = " << list.size() << "\n";

    std::cout << "\n--- reverse() ---\n";
    list.reverse();
    list.print();
    list.printReverse();

    std::cout << "\n--- pop_front() и pop_back() ---\n";
    list.pop_front();
    list.pop_back();
    list.print();

    std::cout << "\n--- Обход через итератор (вперёд) ---\n";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "\n--- Обход через итератор (назад, --it) ---\n";
    auto it = list.begin();
    while (it != list.end()) {
        auto next = it;
        ++next;
        if (next == list.end()) break;  // it — последний узел
        it = next;
    }
    // it теперь на последнем узле. Идём назад до begin().
    while (true) {
        std::cout << *it << " ";
        if (it == list.begin()) break;
        --it;
    }
    std::cout << "\n";

    std::cout << "\n--- merge двух отсортированных списков ---\n";
    DoublyLinkedList<int> first;
    first.push_back(1);
    first.push_back(3);
    first.push_back(5);

    DoublyLinkedList<int> second;
    second.push_back(2);
    second.push_back(4);
    second.push_back(6);

    std::cout << "first:  ";
    first.print();
    std::cout << "second: ";
    second.print();

    first.merge(second);
    std::cout << "После merge: ";
    first.print();
    std::cout << "second после merge: ";
    second.print();

    std::cout << "\n--- Сравнение списков (operator==) ---\n";
    DoublyLinkedList<int> x;
    x.push_back(1);
    x.push_back(2);
    DoublyLinkedList<int> y;
    y.push_back(1);
    y.push_back(2);
    DoublyLinkedList<int> z;
    z.push_back(1);
    z.push_back(3);

    std::cout << "x == y? " << (x == y ? "да" : "нет") << "\n";
    std::cout << "x == z? " << (x == z ? "да" : "нет") << "\n";
    std::cout << "x != z? " << (x != z ? "да" : "нет") << "\n";

    std::cout << "\n--- clear() ---\n";
    list.clear();
    std::cout << "size = " << list.size() << ", empty = " << (list.empty() ? "да" : "нет") << "\n";
    list.print();

    std::cout << "\n--- Шаблон со строками ---\n";
    DoublyLinkedList<std::string> words;
    words.push_back("мир");
    words.push_back("труд");
    words.push_front("Привет");
    words.print();
    words.printReverse();
}

// ============================================================
// main
// ============================================================
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    demoSingly();
    demoDoubly();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}