#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "Utils.h"

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::string>> adjList;

public:
    // Function to add an edge to the graph
    void addEdge(const std::string& u, const std::string& v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since it's an undirected graph
    }

    // Function to load the graph from a CSV file
    bool loadFromCSV(const std::string& filename);

    // Function to print the graph
    void printGraph() const;

    // Function to find the shortest path between two nodes
    std::vector<std::string> findShortestPath(const std::string& start, const std::string& end) const;

    // Function to display the graph in a simple visual format
    void showGraph(const std::vector<std::string>& path) const;
};

#endif // GRAPH_H
