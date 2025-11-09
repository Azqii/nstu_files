#include <iostream>
#include <windows.h> // Comment on linux
#include "Graph.h"

#pragma execution_character_set("utf-8")

using std::cout, std::cin, std::endl;

int main() {
    SetConsoleOutputCP(65001);  // Comment on linux
    SetConsoleCP(65001);  // Comment on linux

    auto graph = Graph<int>(0);

    int x;
    while (true) {
        cout << endl << "Выбор действия:" << endl << endl;
        cout << "1. Создать граф с заданным кол-вом вершин" << endl;
        cout << "2. Вставка ребра" << endl;
        cout << "3. Удаление ребра" << endl;
        cout << "4. Число вершин" << endl;
        cout << "5. Число ребер" << endl;
        cout << "6. Проверка наличия ребра" << endl;
        cout << "7. Указание веса ребра" << endl;
        cout << "8. Напечатать структуру графа" << endl;
        cout << "9. Определение центра взвешенного орграфа на основе алгоритма Флойда" << endl;

        cout << endl;
        cin >> x;
        cout << endl;

        try {
            switch (x) {
                case 1: {
                    int size;
                    cin >> size;
                    graph.~Graph();
                    new (&graph) Graph<int>(size);
                    break;
                }
                case 2: {
                    int v1, v2;
                    cin >> v1 >> v2;
                    graph.Insert(v1, v2);
                    break;
                }
                case 3: {
                    int v1, v2;
                    cin >> v1 >> v2;
                    graph.Delete(v1, v2);
                    break;
                }
                case 4: {
                    cout << graph.V() << endl;
                    break;
                }
                case 5: {
                    cout << graph.E() << endl;
                    break;
                }
                case 6: {
                    int v1, v2;
                    cin >> v1 >> v2;
                    cout << graph.Edge(v1, v2) << endl;
                    break;
                }
                case 7: {
                    int v1, v2, weight;
                    cin >> v1 >> v2 >> weight;
                    graph.SetEdge(v1, v2, weight);
                    break;
                }
                case 8: {
                    graph.Show();
                    break;
                }
                case 9: {
                    std::vector<int> centerNodes = graph.Task();
                    std::cout << "Центр: ";
                    for (const int node : centerNodes) {
                        std::cout << node << " ";
                    }
                    break;
                }
                default: {
                    cout << "Такой команды не существует" << endl;
                    break;
                }
            }
        }
        catch(...) {
            std::cout << "Исключение" << std::endl;
        }
    }
    return 0;
}
