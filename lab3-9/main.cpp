#include <windows.h>

#include <iostream>

#include "BST.h"

// Демонстрация BST
void demoBST() {
    std::cout << "=== Демонстрация BST ===\n";

    BST tree;
    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    int n = 10;

    std::cout << "Вставляем: ";
    for (int i = 0; i < n; i++) {
        std::cout << values[i] << " ";
        tree.insert(values[i]);
    }
    std::cout << "\n\n";

    std::cout << "Структура дерева:\n";
    tree.printTree();
    std::cout << "\n";

    std::cout << "Pre-order:  ";
    tree.preOrder();
    std::cout << "In-order:   ";
    tree.inOrder();
    std::cout << "Post-order: ";
    tree.postOrder();

    std::cout << "\nКоличество листьев: " << tree.countLeaves() << "\n";
    std::cout << "Высота: " << tree.height() << "\n";
    std::cout << "Минимум: " << tree.getMin() << "\n";
    std::cout << "Максимум: " << tree.getMax() << "\n\n";

    std::cout << "Поиск 35: " << (tree.search(35) ? "найден" : "не найден") << "\n";
    std::cout << "Поиск 99: " << (tree.search(99) ? "найден" : "не найден") << "\n\n";

    std::cout << "3-й наименьший: " << tree.findKthSmallest(3) << "\n";
    std::cout << "5-й наименьший: " << tree.findKthSmallest(5) << "\n\n";

    std::cout << "Удаляем 20 (лист)\n";
    tree.remove(20);
    std::cout << "In-order: ";
    tree.inOrder();

    std::cout << "Удаляем 30 (один ребёнок)\n";
    tree.remove(30);
    std::cout << "In-order: ";
    tree.inOrder();

    std::cout << "Удаляем 50 (два ребёнка)\n";
    tree.remove(50);
    std::cout << "In-order: ";
    tree.inOrder();
}

// Часть 3 — применение BST
void demoApplication() {
    std::cout << "\n=== Применение BST (часть 3) ===\n";

    BST tree;

    std::cout << "Вставляем 20 чисел: ";
    for (int i = 0; i < 20; i++) {
        int value = (i * 37 + 13) % 100;
        std::cout << value << " ";
        tree.insert(value);
    }
    std::cout << "\n\n";

    std::cout << "Структура дерева:\n";
    tree.printTree();
    std::cout << "\n";

    std::cout << "Отсортированная последовательность: ";
    tree.inOrder();

    std::cout << "Минимум: " << tree.getMin() << "\n";
    std::cout << "Максимум: " << tree.getMax() << "\n";
    std::cout << "Высота: " << tree.height() << "\n\n";

    int target;
    std::cout << "Введите число для удаления: ";
    std::cin >> target;

    std::cout << "После удаления " << target << ": ";
    tree.remove(target);
    tree.inOrder();
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    demoBST();
    demoApplication();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}