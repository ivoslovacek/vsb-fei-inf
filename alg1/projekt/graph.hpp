#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>

typedef std::tuple<unsigned int, unsigned int> two_tuple;

class Graph
{
public:
    class Vertex
    {
    public:
        /// @brief  ID of the Vertex
        unsigned int id;
        /// @brief Was the Vertex visited by a search algorithm
        bool visited;

        Vertex(unsigned int id);
    };

    /// @brief The number of vertices in a Graph
    unsigned int vertex_count = 0;
    /// @brief The number of edges in a Graph
    unsigned int edge_count = 0;
    /// @brief The number of components in a Graph
    unsigned int components_count = 0;

    /// @brief Map of all vertices in a Graph
    std::unordered_map<unsigned int, Graph::Vertex *> vertices;
    /// @brief Adjacency list containing all vertices and its neighbors in a Graph
    std::unordered_map<unsigned int, std::unordered_map<unsigned int, Graph::Vertex *>> adjacency_list;

    Graph(std::string filepath);
    ~Graph();

    Graph::Vertex *findVertex(unsigned int id);
    Graph::Vertex *insertVertex(unsigned int id);
    void insertEdge(unsigned int id1, unsigned int id2);

    unsigned int getLargestComponent(unsigned int &size, std::vector<unsigned int> &component);

    double getGCC(unsigned int id, std::vector<unsigned int> &component);

    void clearState();
    void printGraph();
};