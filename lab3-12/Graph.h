#pragma once

#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

// Взвешенный граф на матрице смежности.
// matrix[u][v] == -1 означает, что ребра (u, v) нет.
class Graph {
   private:
    int verts;                             // число вершин
    std::vector<std::vector<int>> matrix;  // матрица смежности
    bool isDirected;                       // ориентированный ли граф

   public:
    // Создает граф из v вершин; isD — флаг ориентированности
    Graph(int v, bool isD = false) {
        verts = v;
        isDirected = isD;
        matrix.resize(verts);
        for (int i = 0; i < verts; i++) {
            matrix[i].resize(verts, -1);
        }
    }
    ~Graph() = default;

    // Добавляет ребро (u, v) с весом weight
    void addEdge(int u, int v, int weight) {
        if ((u < 0 or u >= verts) or (v < 0 or v >= verts))
            throw std::runtime_error("Выход за границы!");
        matrix[u][v] = weight;
        if (!isDirected) matrix[v][u] = weight;
    }

    // Удаляет ребро (u, v)
    void removeEdge(int u, int v) {
        if ((u < 0 or u >= verts) or (v < 0 or v >= verts))
            throw std::runtime_error("Выход за границы!");
        matrix[u][v] = -1;
        if (!isDirected) matrix[v][u] = -1;
    }

    // Печатает матрицу смежности (-1 = нет ребра)
    void print() {
        for (int i = 0; i < verts; i++) {
            for (int j = 0; j < verts; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Дейкстра с priority_queue: возвращает {расстояния, предки}
    std::pair<std::vector<int>, std::vector<int>> dijkstra(int start) {
        std::vector<int> dist(verts, INT_MAX);
        dist[start] = 0;
        std::vector<int> prev(verts, -1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>>
            pq;
        pq.push({0, start});
        while (!pq.empty()) {
            std::pair<int, int> current = pq.top();
            pq.pop();
            int d = current.first;
            int v = current.second;
            if (dist[v] < d) continue;  // пропуск устаревших записей
            for (int i = 0; i < verts; i++) {
                if (matrix[v][i] != -1) {
                    int dFromV = matrix[v][i] + dist[v];
                    if (dist[i] > dFromV) {
                        dist[i] = dFromV;
                        prev[i] = v;
                        pq.push({dFromV, i});
                    }
                }
            }
        }
        return {dist, prev};
    }

    // Восстановление пути по массиву предков (путь от start к end)
    std::vector<int> getDijkstraPath(int start, int end, const std::vector<int>& prev) {
        if (prev[end] == -1 and start != end) return std::vector<int>();
        std::vector<int> way;
        int current = end;
        way.push_back(current);
        while (current != start) {
            current = prev[current];
            way.push_back(current);
        }
        std::reverse(way.begin(), way.end());
        return way;
    }

    // Флойд-Уоршелл: возвращает {матрицу расстояний, матрицу next для путей}
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> floydWarshall() {
        const int INF = INT_MAX / 2;
        std::vector<std::vector<int>> dist;
        dist.resize(verts);
        for (int i = 0; i < verts; i++) {
            dist[i].resize(verts, -1);
        }
        for (int i = 0; i < verts; i++) {
            for (int j = 0; j < verts; j++) {
                if (i == j) {
                    dist[i][j] = 0;
                } else if (matrix[i][j] != -1) {
                    dist[i][j] = matrix[i][j];
                } else {
                    dist[i][j] = INF;
                }
            }
        }

        std::vector<std::vector<int>> next;
        next.resize(verts);
        for (int i = 0; i < verts; i++) {
            next[i].resize(verts, -1);
        }
        for (int i = 0; i < verts; i++) {
            for (int j = 0; j < verts; j++) {
                if (i == j) {
                    next[i][j] = i;
                } else if (matrix[i][j] != -1) {
                    next[i][j] = j;
                }
            }
        }

        for (int k = 0; k < verts; k++) {
            for (int i = 0; i < verts; i++) {
                for (int j = 0; j < verts; j++) {
                    if (dist[i][k] != INF and dist[k][j] != INF) {
                        int newWay = dist[i][k] + dist[k][j];
                        if (dist[i][j] > newWay) {
                            dist[i][j] = newWay;
                            next[i][j] = next[i][k];
                        }
                    }
                }
            }
        }
        return {dist, next};
    }

    // Восстановление пути по матрице next (путь от u к v)
    std::vector<int> getFloydWarshallPath(int u, int v, const std::vector<std::vector<int>>& next) {
        if (next[u][v] == -1) return std::vector<int>();
        std::vector<int> way;
        int current = u;
        way.push_back(current);
        while (current != v) {
            current = next[current][v];
            way.push_back(current);
        }
        return way;
    }

    // Печатает матрицу расстояний, INF заменяется на "oo"
    void printFloydMatrix(const std::vector<std::vector<int>>& dist) {
        const int INF = INT_MAX / 2;
        for (size_t i = 0; i < dist.size(); i++) {
            for (size_t j = 0; j < dist[i].size(); j++) {
                if (dist[i][j] == INF)
                    std::cout << "oo" << " ";
                else
                    std::cout << dist[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};
