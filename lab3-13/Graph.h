#pragma once

#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#include "DSU.h"

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    bool operator<(const Edge& other) const { return weight < other.weight; }
};

class Graph {
   private:
    int verts;
    std::vector<std::vector<int>> matrix;

   public:
    Graph(int v) {
        verts = v;
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
        matrix[v][u] = weight;
    }

    // Удаляет ребро (u, v)
    void removeEdge(int u, int v) {
        if ((u < 0 or u >= verts) or (v < 0 or v >= verts))
            throw std::runtime_error("Выход за границы!");
        matrix[u][v] = -1;
        matrix[v][u] = -1;
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

    // Оптимизированный алгоритм Прима
    std::pair<int, std::vector<Edge>> primMST_pq(int start) {
        if (start < 0 or start >= verts) throw std::runtime_error("Нет такой вершины!");
        std::vector<int> minEdge(verts, INT_MAX);
        minEdge[start] = 0;
        std::vector<bool> inMST(verts, false);
        std::vector<int> parent(verts, -1);
        using pii = std::pair<int, int>;

        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.push({0, start});
        int totalWeight = 0;
        int count = 0;
        std::vector<Edge> resEdge;

        while (!pq.empty()) {
            int wEdge = pq.top().first;
            int vEdge = pq.top().second;
            pq.pop();

            if (inMST[vEdge]) continue;
            inMST[vEdge] = true;
            totalWeight += wEdge;
            count++;

            if (parent[vEdge] != -1) {
                resEdge.push_back(Edge(parent[vEdge], vEdge, wEdge));
            }

            for (int i = 0; i < verts; i++) {
                if (matrix[vEdge][i] != -1 and !inMST[i] and matrix[vEdge][i] < minEdge[i]) {
                    minEdge[i] = matrix[vEdge][i];
                    parent[i] = vEdge;
                    pq.push({minEdge[i], i});
                }
            }
        }

        if (count != verts) return {-1, {}};
        return {totalWeight, resEdge};
    }

    // Алгоритм Краскала
    std::pair<int, std::vector<Edge>> kruskalMST() {
        std::vector<Edge> resEdge;
        std::vector<Edge> edges;
        for (int i = 0; i < verts; i++) {
            for (int j = i + 1; j < verts; j++) {
                if (matrix[i][j] != -1) {
                    edges.push_back(Edge(i, j, matrix[i][j]));
                }
            }
        }
        std::sort(std::begin(edges), std::end(edges));

        DSU dsu(verts);
        int totalWeight = 0;
        int count = 0;

        for (const Edge& e : edges) {
            if (!dsu.connected(e.u, e.v)) {
                dsu.unite(e.u, e.v);
                totalWeight += e.weight;
                resEdge.push_back(e);
                count++;
                if (count >= verts - 1) break;
            }
        }

        if (count != verts - 1) return {-1, {}};
        return {totalWeight, resEdge};
    }

    // Поиск не связанных компонент
    std::vector<std::vector<int>> findComponents() {
        std::vector<std::vector<int>> res;
        DSU dsu(verts);
        for (int i = 0; i < verts; i++) {
            for (int j = i + 1; j < verts; j++) {
                if (matrix[i][j] != -1) dsu.unite(i, j);
            }
        }

        std::map<int, std::vector<int>> components;
        for (int i = 0; i < verts; i++) {
            components[dsu.find(i)].push_back(i);
        }

        for (const auto& [key, value] : components) {
            res.push_back(value);
        }

        return res;
    }
};
