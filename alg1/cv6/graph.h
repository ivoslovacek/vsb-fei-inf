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

    void insertVertex(int id);
    void insertVertex(int id, std::vector<int> neighborIds);

    Vertex* findVertex(int id); 

    bool findIdDFS(int id);
};
