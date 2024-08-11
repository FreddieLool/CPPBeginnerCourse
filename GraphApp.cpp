#include "GraphApp.h"

void GraphApp::run(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return;
    }

    std::string filename = argv[1];

    if (!graph.loadFromCSV(filename)) {
        std::cerr << "Error reading or validating CSV file." << std::endl;
        return;
    }

    std::cout << "Graph:" << std::endl;
    graph.printGraph();

    std::string start, end;
    std::cout << "Enter the start node: ";
    std::cin >> start;
    std::cout << "Enter the end node: ";
    std::cin >> end;

    std::vector<std::string> path = graph.findShortestPath(start, end);
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

    graph.showGraph(path);
}
