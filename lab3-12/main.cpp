#include <windows.h>

#include <chrono>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Graph.h"

// Замер времени (как в прошлой работе)
template <typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

// Часть 1. Дейкстра: неориентированный граф, priority_queue
void demoDijkstra() {
    std::cout << "=== Часть 1. Алгоритм Дейкстры (неориентированный граф) ===\n\n";

    // Граф из примера 1 методички + изолированная вершина 6
    // для демонстрации обработки недостижимых вершин
    Graph g(7, false);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);

    std::cout << "Матрица смежности:\n";
    g.print();

    auto [dist, prev] = g.dijkstra(0);

    std::cout << "Кратчайшие расстояния от вершины 0:\n";
    for (int i = 0; i < 7; i++) {
        std::cout << " До " << i << ": ";
        if (dist[i] == INT_MAX) {
            std::cout << "недостижима\n";
        } else {
            std::cout << dist[i] << " (путь: ";
            std::vector<int> path = g.getDijkstraPath(0, i, prev);
            for (int v : path) std::cout << v << " ";
            std::cout << ")\n";
        }
    }

    // Демонстрация неориентированности: путь туда и обратно
    std::cout << "\nПроверка симметрии (граф неориентированный):\n";
    std::vector<int> p1 = g.getDijkstraPath(0, 4, prev);
    std::cout << " Путь 0 -> 4: ";
    for (int v : p1) std::cout << v << " ";
    std::cout << "\n";
    // Для обратного пути запускаем Дейкстру от вершины 4
    auto [dist4, prev4] = g.dijkstra(4);
    std::vector<int> p2 = g.getDijkstraPath(4, 0, prev4);
    std::cout << " Путь 4 -> 0: ";
    for (int v : p2) std::cout << v << " ";
    std::cout << "\n";
}

// Часть 2. Флойд-Уоршелл: ориентированный граф + матрица расстояний + пути
void demoFloyd() {
    std::cout << "\n=== Часть 2. Алгоритм Флойда-Уоршелла (ориентированный граф) ===\n\n";

    // Граф из примера 2 методички
    Graph g(4, true);  // флаг направленности — обязательная часть варианта 2
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 2, 1);

    auto [dist, next] = g.floydWarshall();

    std::cout << "Матрица кратчайших расстояний:\n";
    g.printFloydMatrix(dist);

    std::cout << "\nВосстановление путей:\n";
    int pairs[][2] = {{0, 3}, {1, 3}, {3, 0}, {2, 1}};  // 3->0 и 2->1: пути нет
    for (auto [u, v] : pairs) {
        std::vector<int> path = g.getFloydWarshallPath(u, v, next);
        std::cout << " " << u << " -> " << v << ": ";
        if (path.empty()) {
            std::cout << "путь не существует\n";
        } else {
            for (int vertex : path) std::cout << vertex << " ";
            std::cout << "\n";
        }
    }
}

// Часть 3. Сравнение Дейкстры и Флойда на случайном графе из 20 вершин
void comparePart3() {
    std::cout << "\n=== Часть 3. Сравнение результатов на случайном графе ===\n\n";

    srand(42);  // фиксируем зерно для воспроизводимости результатов
    const int V = 20;
    const int INF = INT_MAX / 2;  // тот же сентинел, что в floydWarshall()

    Graph g(V, false);
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (rand() % 100 < 30) {  // плотность ~30%
                g.addEdge(i, j, 1 + rand() % 20);
            }
        }
    }

    int start = rand() % V;
    auto [dist, prev] = g.dijkstra(start);
    auto [distFW, next] = g.floydWarshall();

    std::cout << "Сравнение расстояний от вершины " << start << ":\n\n";
    std::cout << "Вершина\tДейкстра\tФлойд\tСовпадение\n";
    int mismatches = 0;
    for (int i = 0; i < V; i++) {
        bool dInf = (dist[i] == INT_MAX);
        bool fInf = (distFW[start][i] == INF);
        bool match;
        if (dInf && fInf) {
            match = true;  // недостижима в обоих — согласовано
        } else if (dInf != fInf) {
            match = false;  // один говорит «недостижима», другой — нет
        } else {
            match = (dist[i] == distFW[start][i]);
        }
        if (!match) mismatches++;
        std::cout << i << "\t" << (dInf ? "oo" : std::to_string(dist[i])) << "\t\t"
                  << (fInf ? "oo" : std::to_string(distFW[start][i])) << "\t"
                  << (match ? "да" : "НЕТ!") << "\n";
    }
    std::cout << "\nИтог: " << (mismatches == 0 ? "все результаты совпадают" : "есть расхождения!")
              << "\n";
}

// Часть 3. Замеры времени: Дейкстра из одной вершины, Флойд для всех пар
void benchmark() {
    std::cout << "\n=== Часть 3. Замеры времени ===\n\n";
    std::cout << "V\tДейкстра (мкс)\tФлойд (мкс)\n";

    srand(123);
    int sizes[] = {10, 20, 50, 100};
    for (int V : sizes) {
        Graph g(V, false);
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (rand() % 100 < 30) {
                    g.addEdge(i, j, 1 + rand() % 20);
                }
            }
        }
        int start = rand() % V;

        long long tDij = measureTime([&]() { g.dijkstra(start); });
        long long tFW = measureTime([&]() { g.floydWarshall(); });

        std::cout << V << "\t" << tDij << "\t\t" << tFW << "\n";
    }
}

// main
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    demoDijkstra();
    demoFloyd();
    comparePart3();
    benchmark();

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
