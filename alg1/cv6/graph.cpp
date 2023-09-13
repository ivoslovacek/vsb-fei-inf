#include "graph.h"
#include <vector>
#include <stack>

void Graph::insertVertex(int id)
{
    this->vertices.push_back(new Vertex(id));
}

void Graph::insertVertex(int id, std::vector<int> neighborIds)
{
    Vertex *tmp = new Vertex(id);
    this->vertices.push_back(tmp);

    for (auto neighborId : neighborIds)
    {
        Vertex *neighbor = findVertex(neighborId);

        if (neighbor != nullptr)
        {
            tmp->neighbors.push_back(neighbor);
            neighbor->neighbors.push_back(tmp);
        }
    }
}

Graph::Vertex *Graph::findVertex(int id)
{
    for (auto vertex : vertices)
    {
        if (vertex->id == id)
            return vertex;
    }

    return nullptr;
}

bool Graph::findIdDFS(int id)
{
    Vertex *current = vertices.front();
    std::stack<Vertex *> stack;

    stack.push(current);
    current->color = 1;

    while (!stack.empty())
    {
        current = stack.top();
        stack.pop();

        current->color = 0;

        if (current->id == id)
            return true;

        for (auto neighbor : current->neighbors)
        {
            if (neighbor->color == 2)
            {
                stack.push(neighbor);
                neighbor->color = 1;
            }
        }
    }

    return false;
}