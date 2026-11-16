#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

class GraphMatrix {
   private:
    int verts;
    std::vector<std::vector<int>> matrix;

    // Вспомогательный рекурсивный метод для DFS
    void UtilDFS(int start, std::vector<bool>& visited) {
        visited[start] = true;
        std::cout << start << " ";
        for (int i = 0; i < verts; i++) {
            if (matrix[start][i] == 1 and !visited[i]) UtilDFS(i, visited);
        }
    }

   public:
    // Конструктор: инициализация матрицы нулями
    GraphMatrix(int s) {
        verts = s;
        matrix.resize(verts);
        for (size_t i = 0; i < matrix.size(); i++) {
            matrix[i].resize(verts);
        }

        for (size_t u = 0; u < matrix.size(); u++) {
            for (size_t v = 0; v < matrix.size(); v++) {
                matrix[u][v] = 0;
            }
        }
    }

    ~GraphMatrix() = default;

    // Добавление неориентированного ребра
    void addEdge(int u, int v) {
        if ((u < 0 or u >= verts) or (v < 0 or v >= verts))
            throw std::runtime_error("Выход за границы графа!");
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    // Удаление неориентированного ребра
    void removeEdge(int u, int v) {
        if ((u < 0 or u >= verts) or (v < 0 or v >= verts))
            throw std::runtime_error("Выход за границы графа!");
        matrix[u][v] = 0;
        matrix[v][u] = 0;
    }

    // Вывод матрицы смежности
    void print() {
        for (size_t u = 0; u < matrix.size(); u++) {
            for (size_t v = 0; v < matrix.size(); v++) {
                std::cout << matrix[u][v] << " ";
            }
            std::cout << "\n";
        }
    }

    // Рекурсивный поиск в глубину (DFS)
    std::vector<bool> DFS(int start) {
        if (start < 0 or start >= verts) throw std::runtime_error("Выход за границы графа!");
        std::vector<bool> visited;
        visited.resize(verts, false);
        UtilDFS(start, visited);
        std::cout << std::endl;
        return visited;
    }

    // Итеративный поиск в глубину с использованием стека
    std::vector<bool> DFS_iterative(int start) {
        if (start < 0 or start >= verts) throw std::runtime_error("Выход за границы графа!");
        std::vector<bool> visited;
        visited.resize(verts, false);
        std::stack<int> st;
        st.push(start);
        while (!st.empty()) {
            int current = st.top();
            st.pop();
            if (!visited[current]) {
                visited[current] = true;
                std::cout << current << " ";
                for (int i = 0; i < verts; i++) {
                    if (matrix[current][i] == 1 and !visited[i]) st.push(i);
                }
            }
        }
        std::cout << std::endl;
        return visited;
    }

    // Поиск в ширину (BFS) с использованием очереди
    std::vector<bool> BFS(int start) {
        if (start < 0 or start >= verts) throw std::runtime_error("Выход за границы графа!");
        std::vector<bool> visited;
        visited.resize(verts, false);

        std::queue<int> visverts;
        visverts.push(start);
        visited[start] = true;
        while (!visverts.empty()) {
            start = visverts.front();
            std::cout << start << " ";
            visverts.pop();
            for (int i = 0; i < verts; i++) {
                if (matrix[start][i] == 1 and !visited[i]) {
                    visited[i] = true;
                    visverts.push(i);
                }
            }
        }
        std::cout << std::endl;
        return visited;
    }

    // Доп. задача: найти все вершины, достижимые из заданной (вариант 2)
    std::vector<int> printReachable(int start) {
        std::vector<int> reachs;
        std::vector<bool> visited = BFS(start);
        for (int i = 0; i < verts; i++) {
            if (visited[i]) {
                reachs.push_back(i);
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
        return reachs;
    }

    // Поиск и вывод компонент связности
    int printComponents() {
        std::vector<bool> visited;
        visited.resize(verts, false);
        int components = 0;
        for (int i = 0; i < verts; i++) {
            std::vector<bool> localVisited;
            localVisited.resize(verts, false);
            if (!visited[i]) {
                components++;
                std::cout << "Компонента " << components << ": ";
                localVisited = BFS(i);
                for (size_t j = 0; j < verts; j++) {
                    if (visited[j] or localVisited[j]) visited[j] = true;
                }
                std::cout << std::endl;
            }
        }
        std::cout << "Всего компонент: " << components << std::endl;
        return components;
    }

    // Поиск кратчайшего пути в невзвешенном графе (BFS)
    void printShortestPath(int start, int end) {
        if ((start < 0 or start >= verts) or (end < 0 or end >= verts))
            throw std::runtime_error("Выход за границы графа!");
        std::vector<int> prev;
        prev.resize(verts, -1);
        std::vector<bool> visited;
        visited.resize(verts, false);

        std::queue<int> visverts;
        visverts.push(start);
        visited[start] = true;
        while (!visverts.empty()) {
            int current = visverts.front();
            visverts.pop();
            for (int i = 0; i < verts; i++) {
                if (matrix[current][i] == 1 and !visited[i]) {
                    visited[i] = true;
                    prev[i] = current;
                    visverts.push(i);
                }
            }
        }

        int current = end;
        if (visited[end]) {
            std::vector<int> way;
            while (current != start) {
                way.push_back(current);
                current = prev[current];
            }
            way.push_back(start);
            std::reverse(way.begin(), way.end());
            std::cout << way[0] << " ";
            for (size_t i = 1; i < way.size(); i++) {
                std::cout << " -> " << way[i];
            }
        } else {
            std::cout << "Пути нет!";
        }
        std::cout << std::endl;
    }
};