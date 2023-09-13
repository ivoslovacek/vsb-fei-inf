#include <iostream>
#include <chrono>
#include <iomanip>
#include "graph.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "invalid parameters" << std::endl;
        return 1;
    }

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    Graph graf(argv[1]);
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::cout << "Loading the graph: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - now) / std::chrono::milliseconds(1) << "ms" << std::endl;

    std::vector<unsigned int> component;
    unsigned int size = 0;
    now = std::chrono::system_clock::now();
    unsigned int id = graf.getLargestComponent(size, component);
    end = std::chrono::system_clock::now();
    std::cout << "Finding the largest component: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - now) / std::chrono::milliseconds(1) << "ms" << std::endl;

    graf.clearState();

    now = std::chrono::system_clock::now();
    double gcc = graf.getGCC(id, component);
    end = std::chrono::system_clock::now();
    std::cout << "Calculating the global clustering coefficient for the largest component: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - now) / std::chrono::milliseconds(1) << "ms" << std::endl;

    std::cout << "Graph stats:" << std::endl;
    std::cout << "Number of vertices: " << graf.vertex_count << std::endl;
    std::cout << "Number of edges: " << graf.edge_count << std::endl;
    std::cout << "Number of components: " << graf.components_count << std::endl;
    std::cout << "Number of vertices in the largest component: " << size << std::endl;
    std::cout << std::setprecision(16) << "Global clustering coefficient for the largest component: " << gcc << std::endl;

    return 0;
}