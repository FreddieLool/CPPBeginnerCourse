#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool readCSVFile(const std::string& filename, std::unordered_map<std::string, std::vector<std::string>>& graph) {
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

        std::vector<std::string> nodes = splitString(line, ',');
        for (size_t i = 0; i < nodes.size() - 1; ++i) {
            graph[nodes[i]].push_back(nodes[i + 1]);
        }
    }

    return true;
}

void printGraph(const std::unordered_map<std::string, std::vector<std::string>>& graph) {
    for (const auto& pair : graph) {
        std::cout << pair.first << ": ";
        for (const auto& neighbor : pair.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

void showGraph(const std::unordered_map<std::string, std::vector<std::string>>& graph, const std::vector<std::string>& path) {
    std::unordered_set<std::string> pathNodes(path.begin(), path.end());
    std::cout << "\nVisual Graph Representation in a Single Line:\n";
    std::string visualRepresentation;
    for (const auto& pair : graph) {
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

std::vector<std::string> findShortestPath(const std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& start, const std::string& end) {
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

        for (const auto& neighbor : graph.at(node)) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = node;
            }
        }
    }

    return {};
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::unordered_map<std::string, std::vector<std::string>> graph;

    if (!readCSVFile(filename, graph)) {
        std::cerr << "Error reading or validating CSV file." << std::endl;
        return 1;
    }

    std::cout << "Graph:" << std::endl;
    printGraph(graph);

    std::string start, end;
    std::cout << "Enter the start node: ";
    std::cin >> start;
    std::cout << "Enter the end node: ";
    std::cin >> end;

    std::vector<std::string> path = findShortestPath(graph, start, end);
    if (!path.empty()) {
        std::cout << "Shortest path: ";
        for (const auto& node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No path found between " << start << " and " << end << std::endl;
    }

    showGraph(graph, path);

    return 0;
}
