#include <windows.h>

#include <iostream>

#include "GraphMatrix.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Создаем граф на 7 вершин
    GraphMatrix g(7);

    // Строим граф: две отдельные компоненты связности
    // Компонента 1: 0 - 1 - 2 - 3
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    // Компонента 2: 4 - 5 - 6
    g.addEdge(4, 5);
    g.addEdge(5, 6);

    std::cout << "=== Матрица смежности ===" << std::endl;
    g.print();
    std::cout << std::endl;

    std::cout << "=== Обходы графа (от вершины 0) ===" << std::endl;
    std::cout << "Рекурсивный DFS: ";
    g.DFS(0);
    std::cout << "Итеративный DFS: ";
    g.DFS_iterative(0);
    std::cout << "BFS: ";
    g.BFS(0);
    std::cout << std::endl;

    std::cout << "=== Вершины, достижимые из 0 (задача варианта 2) ===" << std::endl;
    g.printReachable(0);
    std::cout << std::endl;

    std::cout << "=== Поиск компонент связности ===" << std::endl;
    g.printComponents();
    std::cout << std::endl;

    std::cout << "=== Кратчайшие пути (BFS) ===" << std::endl;
    std::cout << "Путь от 0 до 3: ";
    g.printShortestPath(0, 3);
    std::cout << "Путь от 0 до 6 (в разных компонентах): ";
    g.printShortestPath(0, 6);
    std::cout << "Путь от 4 до 6: ";
    g.printShortestPath(4, 6);
    std::cout << std::endl;

    std::cout << "=== Демонстрация удаления ребра ===" << std::endl;
    std::cout << "Удаляем ребро 2-3...\n";
    g.removeEdge(2, 3);
    std::cout << "Путь от 0 до 3 после удаления: ";
    g.printShortestPath(0, 3);
    std::cout << std::endl;

    std::cout << "=== Проверка пустого графа ===" << std::endl;
    GraphMatrix empty(0);
    empty.print();
    std::cout << "Пустой граф успешно обработан, программа не упала.\n";

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}