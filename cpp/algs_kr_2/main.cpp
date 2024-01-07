#include "Graph.h"

#include <iostream>

int main() {
    auto graph = Graph(5);

    std::cout << "Empty graph nodes: " << graph.V() << std::endl;
    std::cout << "Empty graph edges: " << graph.E() << std::endl << std::endl;

    std::cout << "Adding edges between 1 -> 3, 5, 2 -> 3 and 3 -> 4, 5" << std::endl << std::endl;
    graph.Insert(1, 3);
    graph.Insert(1, 5);
    graph.Insert(2, 3);
    graph.Insert(3, 4);
    graph.Insert(3, 5);

    std::cout << "Graph with edges without data:" << std::endl;
    graph.Show();
    std::cout << std::endl;

    if (graph.Edge(1, 3)) {
        std::cout << "This line is printed if there's edge between 1 -> 3" << std::endl;
    }
    if (!graph.Edge(1, 4)) {
        std::cout << "This line is printes if there's NO edge between 1 -> 4" << std::endl << std::endl;
    }

    std::cout << "Setting 1 -> 3 edge size to 5 and 3 -> 5 to 6 and deleting 1 -> 5 edge" << std::endl << std::endl;
    graph.SetEdge(1, 3, 5);
    graph.SetEdge(3, 5, 6);
    graph.Delete(1, 5);

    std::cout << "Graph after changes:" << std::endl;
    graph.Show();
    std::cout << std::endl;


    Graph graphTaskTest(5);

    graphTaskTest.Insert(1, 2, 2);
    graphTaskTest.Insert(2, 3, 1);
    graphTaskTest.Insert(3, 4, 3);
    graphTaskTest.Insert(4, 5, 5);
    graphTaskTest.Insert(2, 4, 2);
    graphTaskTest.Insert(3, 5, 1);

    std::cout << "New graph for Task() test: " << std::endl;
    graphTaskTest.Show();

    std::vector<int> centerNodes = graphTaskTest.Task();

    std::cout << "Center nodes: ";
    for (const int node : centerNodes) {
        std::cout << node << " ";
    }

    return 0;
}
