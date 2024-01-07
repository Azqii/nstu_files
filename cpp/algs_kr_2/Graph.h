//
// Created by DimaWin on 07.01.2024.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>


class Graph {
private:
    // Кол-во вершин в графе
    int size;

    // Массив со списками смежности, хранящими номер соединенной вершины и размер ребра
    std::vector<std::pair<int, int>>* edges;

    void throwIfInvalidNodes(int v1, int v2) const;

public:
    explicit Graph(int size);
    ~Graph();
    int V() const;
    int E() const;
    void Insert(int v1, int v2, int weight = 0);
    void Delete(int v1, int v2);
    bool Edge(int v1, int v2);
    void SetEdge(int v1, int v2, int data);
    std::vector<int> Task() const;
    void Show() const;
};


#endif //GRAPH_H
