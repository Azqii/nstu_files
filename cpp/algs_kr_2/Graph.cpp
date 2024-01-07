//
// Created by DimaWin on 07.01.2024.
//

#include "Graph.h"

#include <stdexcept>
#include <iostream>
#include <limits>


Graph::Graph(int const size) {
    this->size = size;
    this->edges = new std::vector<std::pair<int, int>>[size];
}

Graph::~Graph() {
    delete[] this->edges;
}

void Graph::throwIfInvalidNodes(const int v1, const int v2) const {
    if (v1 < 1 || v1 > this->size || v2 < 1 || v2 > this->size) {
        throw std::invalid_argument("There's no such node in graph");
    }
}


int Graph::V() const {
    return this->size;
}

int Graph::E() const {
    int counter = 0;
    for (int i = 0; i < this->size; i++) {
        counter += this->edges[i].size();
    }
    return counter;
}

void Graph::Insert(const int v1, const int v2, const int weight) {
    this->throwIfInvalidNodes(v1, v2);

    for (const auto& edge : this->edges[v1 - 1]) {
        if (edge.first == v2) {
            throw std::invalid_argument("The graph already has edge between these nodes");
        }
    }
    this->edges[v1 - 1].emplace_back(v2, weight);
}

void Graph::Delete(const int v1, const int v2) {
    this->throwIfInvalidNodes(v1, v2);

    for (auto it = this->edges[v1 - 1].begin(); it != this->edges[v1 - 1].end(); ++it) {
        if (it->first == v2) {
            this->edges->erase(it);
            return;
        }
    }
    throw std::invalid_argument("There is no such edge between these nodes");
}

bool Graph::Edge(const int v1, const int v2) {
    this->throwIfInvalidNodes(v1, v2);

    for (const auto& edge : this->edges[v1 - 1]) {
        if (edge.first == v2) {
            return true;
        }
    }
    return false;
}

void Graph::SetEdge(const int v1, const int v2, const int weight) {
    this->throwIfInvalidNodes(v1, v2);

    for (auto& edge : this->edges[v1 - 1]) {
        if (edge.first == v2) {
            edge.second = weight;
            return;
        }
    }
    throw std::invalid_argument("There is no such edge between these nodes");
}

void Graph::Show() const {
    for (int i = 0; i < this->size; i++) {
        std::cout << i + 1 << "-->";
        for (const auto& edge : this->edges[i]) {
            std::cout << "---(" << edge.second << ")---" << edge.first;
        }
        std::cout << std::endl;
    }
}

std::vector<int> Graph::Task() const {
    // Создаем матрицу расстояний и инициализируем ее значениями std::numeric_limits<int>::max()
    std::vector<std::vector<int>> distanceMatrix(size, std::vector<int>(size, std::numeric_limits<int>::max()));

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
                    distanceMatrix[i][k] != std::numeric_limits<int>::max() &&
                    distanceMatrix[k][j] != std::numeric_limits<int>::max() &&
                    distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]
                ) {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                }
            }
        }
    }

    // Находим минимальный эксцентриситет и соответствующий ему центр графа
    int minEccentricity = std::numeric_limits<int>::max();
    std::vector<int> centerNodes;
    for (int j = 0; j < this->size; j++) {
        int maxDistance = 0;

        for (int i = 0; i < this->size; i++) {
            if (distanceMatrix[i][j] != std::numeric_limits<int>::max()) {
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
