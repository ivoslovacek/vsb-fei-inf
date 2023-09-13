#pragma once

#include <vector>

class Graph
{
public:
    class Vertex
    {
    public:
        int id;

        std::vector<Vertex *> neighbors;

        int color = 2;

        Vertex(int id)
        {
            this->id = id;
        }
    };

    std::vector<Vertex *> vertices;
    ~Graph();

    void insertVertex(int id);
    void insertVertex(int id, std::vector<int> neighborIds);

    Vertex *findVertex(int id);

    void createDirectedEdge(int id, int id2);

    void topologicalSort(std::vector<int> &sortedVertices);
    bool visit(Vertex *vertex, std::vector<int> &sortedVertices);

    bool findIdDFS(int id);
};
