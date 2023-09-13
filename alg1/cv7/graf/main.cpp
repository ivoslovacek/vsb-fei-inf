#include <iostream>

#include "graph.h"

int main()
{
    Graph g;

    /*g.insertVertex(1);

    std::vector<int> neighborIds;
    neighborIds.push_back(1);

    g.insertVertex(2, neighborIds);

    neighborIds.clear();
    neighborIds.push_back(1);
    neighborIds.push_back(2);

    g.insertVertex(3, neighborIds);

    neighborIds.clear();
    neighborIds.push_back(3);

    g.insertVertex(4, neighborIds);
    g.insertVertex(5, neighborIds);

    g.insertVertex(6);
    g.insertVertex(7);

    neighborIds.clear();
    neighborIds.push_back(6);
    neighborIds.push_back(7);
    neighborIds.push_back(3);

    g.insertVertex(8, neighborIds);

    neighborIds.clear();
    neighborIds.push_back(2);
    neighborIds.push_back(8);

    g.insertVertex(9);

    neighborIds.clear();
    neighborIds.push_back(10);*/

    for (int i = 1; i <= 10; i++)
    {
        g.insertVertex(i);
    }

    g.createDirectedEdge(1, 2);
    g.createDirectedEdge(1, 3);
    g.createDirectedEdge(2, 3);
    g.createDirectedEdge(2, 9);
    g.createDirectedEdge(3, 4);
    g.createDirectedEdge(3, 5);
    g.createDirectedEdge(3, 8);
    g.createDirectedEdge(8, 6);
    g.createDirectedEdge(8, 7);
    g.createDirectedEdge(8, 9);
    g.createDirectedEdge(9, 10);

    std::vector<int> sorted;
    g.topologicalSort(sorted);

    for (auto vertex : sorted)
    {
        std::cout << vertex << " ";
    }

    //std::cout << "Vertex " << (g.findIdDFS(5) ? "" : "not ") << "found." << std::endl;

    return 0;
}