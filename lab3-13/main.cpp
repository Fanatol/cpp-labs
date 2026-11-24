#include <windows.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Graph.h"

// Печатает список рёбер MST в едином формате (части 1 и 2)
void printEdges(const std::vector<Edge>& edges) {
    if (edges.empty()) {
        std::cout << "  (нет рёбер)" << std::endl;
        return;
    }
    for (const Edge& e : edges) {
        std::cout << "  " << e.u << " - " << e.v << " (вес: " << e.weight << ")" << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // === Часть 1. Алгоритм Прима ===
    std::cout << "=== Часть 1. Алгоритм Прима ===" << std::endl;

    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    std::cout << "Матрица смежности:" << std::endl;
    g.print();

    std::pair<int, std::vector<Edge>> res = g.primMST_pq(0);
    if (res.first == -1) {
        std::cout << "Граф не связный!" << std::endl;
    } else {
        std::cout << "Рёбра минимального остовного дерева:" << std::endl;
        printEdges(res.second);
        std::cout << "Общий вес MST: " << res.first << std::endl;
    }

    // Демонстрация обработки несвязности
    Graph g2(3);
    g2.addEdge(0, 1, 5);

    std::cout << "\nНесвязный граф:" << std::endl;
    g2.print();

    std::pair<int, std::vector<Edge>> res2 = g2.primMST_pq(0);
    if (res2.first == -1) std::cout << "Граф не связный!" << std::endl;

    // === Часть 2. Алгоритм Краскала ===
    std::cout << "\n=== Часть 2. Алгоритм Краскала ===" << std::endl;

    Graph g3(5);
    g3.addEdge(0, 1, 2);
    g3.addEdge(0, 3, 6);
    g3.addEdge(1, 2, 3);
    g3.addEdge(1, 3, 8);
    g3.addEdge(1, 4, 5);
    g3.addEdge(2, 4, 7);
    g3.addEdge(3, 4, 9);

    std::cout << "Матрица смежности:" << std::endl;
    g3.print();

    std::pair<int, std::vector<Edge>> res3 = g3.kruskalMST();
    if (res3.first == -1) {
        std::cout << "Граф не связный!" << std::endl;
    } else {
        std::cout << "Рёбра минимального остовного дерева:" << std::endl;
        printEdges(res3.second);
        std::cout << "Общий вес MST: " << res3.first << std::endl;
    }

    // === Часть 3. Прокладка сетей ===
    std::cout << "\n=== Часть 3. Прокладка сетей ===" << std::endl;

    int n;
    std::cout << "Введите количество городов: ";
    std::cin >> n;

    std::vector<std::string> names(n);  // индекс -> имя города
    std::map<std::string, int> id;      // имя города -> индекс
    std::cout << "Введите названия городов через пробел: ";
    for (int i = 0; i < n; i++) {
        std::cin >> names[i];
        id[names[i]] = i;
    }

    int m;
    std::cout << "Введите количество дорог: ";
    std::cin >> m;

    Graph cityGraph(n);
    std::cout << "Введите дороги в формате Имя1-Имя2 вес:" << std::endl;
    for (int i = 0; i < m; i++) {
        std::string token;
        int w;
        std::cin >> token >> w;

        // Разделяем токен вида "A-B" на два имени
        size_t pos = token.find('-');
        if (pos == std::string::npos or id.find(token.substr(0, pos)) == id.end() or
            id.find(token.substr(pos + 1)) == id.end()) {
            std::cout << "Ошибка: дорога \"" << token << "\" задана неверно!" << std::endl;
            return 1;
        }
        cityGraph.addEdge(id[token.substr(0, pos)], id[token.substr(pos + 1)], w);
    }

    std::pair<int, std::vector<Edge>> net = cityGraph.kruskalMST();
    if (net.first == -1) {
        // Граф несвязный — выводим компоненты с именами городов
        std::cout << "Соединить все города невозможно!" << std::endl;
        std::cout << "Компоненты связности:" << std::endl;
        std::vector<std::vector<int>> comps = cityGraph.findComponents();
        int num = 1;
        for (const std::vector<int>& comp : comps) {
            std::cout << "  Компонента " << num++ << ": ";
            for (int k = 0; k < (int)comp.size(); k++) {
                std::cout << names[comp[k]];
                if (k + 1 < (int)comp.size()) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    } else {
        // Граф связный — минимальная стоимость и список дорог
        std::cout << "Минимальная стоимость: " << net.first << std::endl;
        std::cout << "Дороги для строительства:" << std::endl;
        for (const Edge& e : net.second) {
            std::cout << "  " << names[e.u] << " - " << names[e.v] << " (" << e.weight << ")"
                      << std::endl;
        }
    }

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
