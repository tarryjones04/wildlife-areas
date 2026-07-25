#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <algorithm>

// Structure to represent an edge with weight (distance in km)
struct Edge {
    std::string destination;
    double distance;

    Edge(const std::string& dest, double dist) 
        : destination(dest), distance(dist) {}
};

// Graph class using adjacency list representation
class Graph {
private:
    // Adjacency list: conservation area -> list of edges
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    // Sorted list of areas for consistent matrix ordering
    std::vector<std::string> areas;

public:
    Graph() {}

    // Add a conservation area (node) to the graph
    void addArea(const std::string& area) {
        if (adjacencyList.find(area) == adjacencyList.end()) {
            adjacencyList[area] = std::vector<Edge>();
            areas.push_back(area);
            std::cout << "Added conservation area: " << area << std::endl;
        } else {
            std::cout << "Area " << area << " already exists." << std::endl;
        }
    }

    // Add a connection between two areas with distance in km
    void addConnection(const std::string& area1, const std::string& area2, double distance) {
        // Ensure both areas exist
        if (adjacencyList.find(area1) == adjacencyList.end()) {
            addArea(area1);
        }
        if (adjacencyList.find(area2) == adjacencyList.end()) {
            addArea(area2);
        }

        // Check if connection already exists
        for (const auto& edge : adjacencyList[area1]) {
            if (edge.destination == area2) {
                std::cout << "Connection between " << area1 << " and " << area2 
                          << " already exists." << std::endl;
                return;
            }
        }

        // Add bidirectional connection (undirected graph)
        adjacencyList[area1].emplace_back(area2, distance);
        adjacencyList[area2].emplace_back(area1, distance);

        std::cout << "Added connection: " << area1 << " <-> " << area2 
                  << " (" << distance << " km)" << std::endl;
    }

    // Display the entire graph as adjacency list
    void displayGraph() const {
        std::cout << "\n=== Graph Structure (Adjacency List) ===" << std::endl;
        for (const auto& [area, edges] : adjacencyList) {
            std::cout << "\nArea: " << area << std::endl;
            std::cout << "Connected to:" << std::endl;
            for (const auto& edge : edges) {
                std::cout << "  -> " << edge.destination << " (" << edge.distance << " km)" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    // Display the graph as adjacency matrix
    void displayAdjacencyMatrix() const {
        if (areas.empty()) {
            std::cout << "Graph is empty. No matrix to display." << std::endl;
            return;
        }

        std::cout << "\n=== Adjacency Matrix Representation ===" << std::endl;
        std::cout << "(0 indicates no direct connection)\n" << std::endl;

        // Sort areas for consistent ordering
        std::vector<std::string> sortedAreas = areas;
        std::sort(sortedAreas.begin(), sortedAreas.end());

        // Calculate column widths
        int maxWidth = 0;
        for (const auto& area : sortedAreas) {
            maxWidth = std::max(maxWidth, static_cast<int>(area.length()));
        }
        maxWidth = std::max(maxWidth, 8); // Minimum width for headers

        // Print header row
        std::cout << std::setw(maxWidth) << " ";
        for (const auto& area : sortedAreas) {
            std::cout << std::setw(maxWidth) << area.substr(0, maxWidth);
        }
        std::cout << std::endl;

        // Print separator
        std::cout << std::string(maxWidth, '-');
        for (size_t i = 0; i < sortedAreas.size(); ++i) {
            std::cout << std::string(maxWidth, '-');
        }
        std::cout << std::endl;

        // Print matrix rows
        for (const auto& area1 : sortedAreas) {
            std::cout << std::setw(maxWidth) << area1.substr(0, maxWidth);

            for (const auto& area2 : sortedAreas) {
                if (area1 == area2) {
                    std::cout << std::setw(maxWidth) << "0";
                } else {
                    double distance = getDistanceInternal(area1, area2);
                    if (distance > 0) {
                        std::cout << std::setw(maxWidth) << std::fixed << std::setprecision(1) << distance;
                    } else {
                        std::cout << std::setw(maxWidth) << "0";
                    }
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Get all neighbors of a conservation area
    void getNeighbors(const std::string& area) const {
        if (adjacencyList.find(area) == adjacencyList.end()) {
            std::cout << "Area " << area << " not found in graph." << std::endl;
            return;
        }

        std::cout << "\nNeighbors of " << area << ":" << std::endl;
        const auto& edges = adjacencyList.at(area);
        if (edges.empty()) {
            std::cout << "  No neighbors." << std::endl;
        } else {
            for (const auto& edge : edges) {
                std::cout << "  - " << edge.destination << " (" << edge.distance << " km away)" << std::endl;
            }
        }
    }

    // Get the distance between two areas
    double getDistance(const std::string& area1, const std::string& area2) const {
        if (adjacencyList.find(area1) == adjacencyList.end()) {
            std::cout << "Area " << area1 << " not found." << std::endl;
            return -1.0;
        }

        const auto& edges = adjacencyList.at(area1);
        for (const auto& edge : edges) {
            if (edge.destination == area2) {
                return edge.distance;
            }
        }

        std::cout << "No direct connection between " << area1 << " and " << area2 << std::endl;
        return -1.0;
    }

    // Internal method to get distance without printing errors
    double getDistanceInternal(const std::string& area1, const std::string& area2) const {
        if (adjacencyList.find(area1) == adjacencyList.end()) {
            return -1.0;
        }

        const auto& edges = adjacencyList.at(area1);
        for (const auto& edge : edges) {
            if (edge.destination == area2) {
                return edge.distance;
            }
        }

        return -1.0;
    }

    // Get the number of areas in the graph
    int getNumberOfAreas() const {
        return adjacencyList.size();
    }

    // Get the total number of connections
    int getNumberOfConnections() const {
        int count = 0;
        for (const auto& [area, edges] : adjacencyList) {
            count += edges.size();
        }
        return count / 2; // Divide by 2 because each connection is counted twice
    }
};

#endif // GRAPH_HPP
