#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include "graph.hpp"

/**
 Constructor for a Graph that loads all vertices
 from a file

 @param filepath The path to the file 
*/
Graph::Graph(std::string filepath)
{
    int vertex1, vertex2;
    std::ifstream graphfile;
    graphfile.open(filepath);

    if (!graphfile.is_open())
    {
        std::cerr << "File could not be opened" << std::endl;
        exit(1);
    }

    while (!graphfile.eof())
    {
        vertex1 = 0;
        vertex2 = 0;
        graphfile >> vertex1 >> vertex2;
        if (!graphfile.fail())
        {
            this->insertEdge(vertex1, vertex2);
        }
    }
    graphfile.close();
}


/**
 Destructor for a Graph that free all vertices in a Graph
*/
Graph::~Graph()
{
    for (auto &vertex : this->vertices)
    {
        delete vertex.second;
    }
}

/**
 Constructor for creating a Vertex

 @param id The id of the Vertex being created
*/
Graph::Vertex::Vertex(unsigned int id)
{
    this->id = id;
    this->visited = false;
}

/**
 Find a Vertex in a Graph

 @param id Id of the wanted Vertex
 @return Pointer to the Vertex or nullptr if the Vertex doesn't exist 
*/
Graph::Vertex *Graph::findVertex(unsigned int id)
{
    if (this->vertices.find(id) != this->vertices.end())
        return this->vertices[id];
    else
        return nullptr;
}

/**
 Inserts an creates a new Vertex inside a Graph

 @param id Id of the Vertex to be created
 @return Pointer to the Vertex
*/
Graph::Vertex *Graph::insertVertex(unsigned int id)
{
    this->vertex_count++;

    Vertex *tmp = new Vertex(id);

    this->vertices[id] = tmp;

    return tmp;
}

/**
 Creates an edge between two vertices in a Graph

 @param id1 The id of the first Vertex
 @param id2 The id of the second Vertex
*/
void Graph::insertEdge(unsigned int id1, unsigned int id2)
{
    this->edge_count++;

    if (id1 == id2)
    {
        Vertex *tmp1 = findVertex(id1);
        if (tmp1 == nullptr)
        {
            tmp1 = insertVertex(id1);
        }

        this->adjacency_list[id1][id2] = tmp1;
        return;
    }

    Vertex *tmp1 = findVertex(id1);
    Vertex *tmp2 = findVertex(id2);

    if (tmp1 == nullptr)
    {
        tmp1 = insertVertex(id1);
    }

    if (tmp2 == nullptr)
    {
        tmp2 = insertVertex(id2);
    }

    this->adjacency_list[id1][id2] = tmp2;
    this->adjacency_list[id2][id1] = tmp1;
}

/**
 Prints the Vertex::id of every Vertex stored in Graph
*/
void Graph::printGraph()
{
    for (auto vertex : this->vertices)
    {
        std::cout <<  vertex.second->id << std::endl;

    }
}

/**
 Sets the visited attribute of every Vertex stored to false
*/
void Graph::clearState()
{
    for (auto vertex : this->vertices)
    {
        vertex.second->visited = false;
    }
}

/**
 Finds the component in which a specified vertex is located

 @param graph reference to a graph in which it will search
 @param id id of a vertex for which I want to find the component
 @param component reference to a vector where ids of found vertices will be stored
 @return returns the size of the component
*/
unsigned int getComponent(Graph &graph, unsigned int id, std::vector<unsigned int> &component)
{
    std::stack<Graph::Vertex *> stack;
    stack.push(graph.findVertex(id));
    stack.top()->visited = true;

    while (!stack.empty())
    {
        Graph::Vertex *current = stack.top();
        stack.pop();
        component.push_back(current->id);

        for (auto each : graph.adjacency_list[current->id])
        {
            if (!each.second->visited)
            {
                stack.push(each.second);
                each.second->visited = true;
            }
        }
    }

    return component.size();
}

/**
 Finds the largest component of a Graph represented by a adjacency list

 @param size reference to an unsigned integer where the size of the component will be stored
 @param component reference to a std::vector of unsigned int where ids of Vertexes insied the component will be stored
 @return An id of a vertex located inside of the component
*/
unsigned int Graph::getLargestComponent(unsigned int &size, std::vector<unsigned int> &component)
{
    // Initialize the id of a vertex inside of the graph
    unsigned int tmp = this->vertices.begin()->second->id;
    // Set the size of the component to zero
    size = 0;

    // Iterate trought every vertex stored in the graph
    for (auto vertex : this->vertices)
    {
        // Check if the vertex was already visited
        if (!vertex.second->visited)
        {
            // Find a new component that includes the vertex
            std::vector<unsigned int> tmp_component;
            unsigned int tmp_size = getComponent(*this, vertex.second->id, tmp_component);
            this->components_count++;

            // Check if the size of the component is larger then then the size
            // of the largest found component so far
            if (tmp_size > size)
            {
                // Set the largest found component, its size and an index
                // of a vertex inside the component
                component.clear();
                component = tmp_component;
                size = tmp_size;
                tmp = vertex.second->id;
            }
        }
    }

    // Return an id of a vertex inside the largest found component
    return tmp;
}

/**
 Calculate the number of open and closed triplets in a subgraph of the graph represented
 by the specified adjacency list that contains the vertex with the specified ID.

 @param adjacency_list The adjacency list representing the graph.
 @param id The ID of the vertex to calculate the count of triplets for.
 @return The count of triplets with vertex ID as a the base of the triplet.
*/

inline unsigned int getTripletsCount(std::unordered_map<unsigned int, std::unordered_map<unsigned int, Graph::Vertex *>> &adjacency_list, unsigned int id)
{
    unsigned int x = (unsigned int)adjacency_list[id].size() * (unsigned int)(adjacency_list[id].size() - 1);
    return x;
}

/**
 Calculates the number of triangles in a subgraph of the graph represented by the specified adjacency list
 that contains the Vertex with the specified ID.

 @param adjacency_list The adjacency list representing the graph.
 @param id The ID of the Vertex to calculate the triangle count for.
 @return The number of triangles in the subgraph containing the specified Vertex.
*/
inline unsigned int getTriangleCount(std::unordered_map<unsigned int, std::unordered_map<unsigned int, Graph::Vertex *>> &adjacency_list, unsigned int id)
{
    // Initialize triangle count to zero
    unsigned int count = 0;

    // Iterate over all neighbors of the vertex with the specified ID
    for (auto i : adjacency_list[id])
    {
        // Iterate over all neighbors of the neighbor
        for (auto j : adjacency_list[i.second->id])
        {
            // Check if the neighbor and the neighbor of the neighbor are distinct and
            // if there is an edge from the neighbor of the neighbor to the original vertex
            if (i.first ^ j.first)
                count += adjacency_list[id].count(j.second->id);
        }
    }

    // Return the number of triangles in the subgraph
    return count;
}

/**
 Calculates the global clustering coefficient (GCC) for a given component
 starting from a Vertex with the specified ID.

 @param id The ID of the Vertex to start from.
 @param component A vector of Vertex IDs representing the component to calculate the GCC for.
 @return The GCC for the given component starting from the specified Vertex.
*/
double Graph::getGCC(unsigned int id, std::vector<unsigned int> &component)
{
    // Initialize triplet and closed triplet counts to zero
    unsigned int triplets = 0;
    unsigned int closedTriplets = 0;

    // Iterate over all vertices in the component
    for (auto vertex : component)
    {
        // Update triplet and closed triplet counts for current vertex
        triplets += getTripletsCount(this->adjacency_list, vertex);
        closedTriplets += getTriangleCount(this->adjacency_list, vertex);
    }

    // Calculate and return the GCC for the component
    return (double)(closedTriplets) / (double)(triplets);
}