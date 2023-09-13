#include <iostream>

#include "graph.h"

int main()
{
    Graph g;

    g.insertVertex(1);

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
    neighborIds.push_back(10);

    std::cout << "Vertex " << (g.findIdDFS(5) ? "" : "not ") << "found." << std::endl;

    return 0;
}