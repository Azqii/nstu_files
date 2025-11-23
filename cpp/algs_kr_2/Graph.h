//
// Created by DimaWin on 07.01.2024.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <stdexcept>
#include <iostream>
#include <limits>


template <class W>
class Graph {
private:
    // Кол-во вершин в графе
    int size;
    // Массив со списками смежности, хранящими номер соединенной вершины и размер ребра
    std::vector<std::pair<int, W>>* edges;

    void throwIfInvalidNodes(int v1, int v2) const;

public:
    Graph(const Graph&) = delete;            // Запрет копирования
    Graph& operator=(const Graph&) = delete; // Запрет присваивания
    explicit Graph(int size);
    ~Graph();
    int V() const;
    int E() const;
    void Insert(int v1, int v2, W weight = 0);
    void Delete(int v1, int v2);
    bool Edge(int v1, int v2);
    void SetEdge(int v1, int v2, W weight);
    std::vector<int> Task() const;
    void Show() const;
};

template <class W>
Graph<W>::Graph(int const size) {
    this->size = size;
    this->edges = new std::vector<std::pair<int, W>>[size];
}

template <class W>
Graph<W>::~Graph() {
    delete[] this->edges;
}

template <class W>
void Graph<W>::throwIfInvalidNodes(const int v1, const int v2) const {
    if (v1 < 1 || v1 > this->size || v2 < 1 || v2 > this->size) {
        throw std::invalid_argument("В графе нет такого узла");
    }
}

template <class W>
int Graph<W>::V() const {
    return this->size;
}

template <class W>
int Graph<W>::E() const {
    int counter = 0;
    for (int i = 0; i < this->size; i++) {
        counter += this->edges[i].size();
    }
    return counter;
}

template <class W>
void Graph<W>::Insert(const int v1, const int v2, const W weight) {
    this->throwIfInvalidNodes(v1, v2);

    for (const auto& edge : this->edges[v1 - 1]) {
        if (edge.first == v2) {
            throw std::invalid_argument("У графа уже есть ребро между этими узлами");
        }
    }
    this->edges[v1 - 1].emplace_back(v2, weight);
}

template <class W>
void Graph<W>::Delete(const int v1, const int v2) {
    this->throwIfInvalidNodes(v1, v2);

    for (auto it = this->edges[v1 - 1].begin(); it != this->edges[v1 - 1].end(); ++it) {
        if (it->first == v2) {
            this->edges[v1 - 1].erase(it);
            return;
        }
    }
    throw std::invalid_argument("У графа нет ребра между этими узлами");
}

template <class W>
bool Graph<W>::Edge(const int v1, const int v2) {
    this->throwIfInvalidNodes(v1, v2);

    for (const auto& edge : this->edges[v1 - 1]) {
        if (edge.first == v2) {
            return true;
        }
    }
    return false;
}

template <class W>
void Graph<W>::SetEdge(const int v1, const int v2, const W weight) {
    this->throwIfInvalidNodes(v1, v2);

    for (auto& edge : this->edges[v1 - 1]) {
        if (edge.first == v2) {
            edge.second = weight;
            return;
        }
    }
    throw std::invalid_argument("У графа нет ребра между этими узлами");
}

template <class W>
void Graph<W>::Show() const {
    for (int i = 0; i < this->size; i++) {
        std::cout << i + 1 << "-->";
        for (const auto& edge : this->edges[i]) {
            std::cout << "---(" << edge.second << ")---" << edge.first;
        }
        std::cout << std::endl;
    }
}

template <class W>
std::vector<int> Graph<W>::Task() const {
    // Создаем матрицу расстояний и инициализируем ее значениями std::W<W>::max()
    std::vector<std::vector<W>> distanceMatrix(size, std::vector<W>(size, std::numeric_limits<W>::max()));

    // Инициализация диагонали нулями
    for (int i = 0; i < size; ++i) {
        distanceMatrix[i][i] = 0;
    }

    // Инициализация расстояний для существующих ребер
    for (int i = 0; i < size; ++i) {
        for (const auto& edge : edges[i]) {
            distanceMatrix[i][edge.first - 1] = edge.second;
        }
    }

    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (
                        distanceMatrix[i][k] != std::numeric_limits<W>::max() &&
                        distanceMatrix[k][j] != std::numeric_limits<W>::max() &&
                        distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]
                        ) {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                }
            }
        }
    }

    // Находим минимальный эксцентриситет и соответствующий ему центр графа
    W minEccentricity = std::numeric_limits<W>::max();
    std::vector<int> centerNodes;
    for (int j = 0; j < this->size; j++) {
        W maxDistance = 0;

        for (int i = 0; i < this->size; i++) {
            if (distanceMatrix[i][j] != std::numeric_limits<W>::max()) {
                maxDistance = std::max(maxDistance, distanceMatrix[i][j]);
            }
        }

        if (maxDistance < minEccentricity && maxDistance != 0) {
            minEccentricity = maxDistance;
            centerNodes.clear();
            centerNodes.push_back(j + 1);
        }
        else if (maxDistance == minEccentricity) {
            centerNodes.push_back(j + 1);
        }
    }

    return centerNodes;
}

#endif //GRAPH_H
