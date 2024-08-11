#include "Graph.h"
#include <fstream>

bool Graph::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Can't open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        for (char c : line) {
            if (!isalpha(c) && c != ',') {
                std::cerr << "Invalid character in file: " << c << std::endl;
                return false;
            }
        }

        std::vector<std::string> nodes = Utils::splitString(line, ',');
        for (size_t i = 0; i < nodes.size() - 1; ++i) {
            addEdge(nodes[i], nodes[i + 1]);
        }
    }
    return true;
}

void Graph::printGraph() const {
    for (const auto& pair : adjList) {
        std::cout << pair.first << ": ";
        for (const auto& neighbor : pair.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> Graph::findShortestPath(const std::string& start, const std::string& end) const {
    std::unordered_map<std::string, std::string> parent;
    std::unordered_set<std::string> visited;
    std::queue<std::string> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        std::string node = q.front();
        q.pop();

        if (node == end) {
            std::vector<std::string> path;
            for (std::string at = end; at != ""; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : adjList.at(node)) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = node;
            }
        }
    }

    return {};
}

void Graph::showGraph(const std::vector<std::string>& path) const {
    std::unordered_set<std::string> pathNodes(path.begin(), path.end());
    std::cout << "\nVisual Graph Representation:\n";
    std::string visualRepresentation;
    for (const auto& pair : adjList) {
        for (const auto& neighbor : pair.second) {
            std::string edge = pair.first + " -> " + neighbor;
            bool isPathEdge = false;
            for (size_t i = 0; i < path.size() - 1; ++i) {
                if (pair.first == path[i] && neighbor == path[i + 1]) {
                    isPathEdge = true;
                    break;
                }
            }
            if (isPathEdge) {
                visualRepresentation += "[" + pair.first + "] -> [" + neighbor + "] ";
            }
            else {
                visualRepresentation += pair.first + " -> " + neighbor + " ";
            }
        }
    }
    std::cout << visualRepresentation << std::endl;
}
