#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <limits>

// Structure to represent an edge with weight (distance in km)
struct Edge {
    std::string destination;
    double distance;

    Edge(const std::string& dest, double dist) 
        : destination(dest), distance(dist) {}
};

// Structure to represent a connection for sorting
struct Connection {
    std::string area1;
    std::string area2;
    double distance;

    Connection(const std::string& a1, const std::string& a2, double dist)
        : area1(a1), area2(a2), distance(dist) {}

    // Comparison operator for sorting by distance
    bool operator<(const Connection& other) const {
        return distance < other.distance;
    }
};

// Structure to represent a node for Dijkstra's algorithm
struct Node {
    std::string area;
    double distance;

    Node(const std::string& a, double d) : area(a), distance(d) {}

    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
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

    // Display connections sorted by distance (smallest to largest)
    void displayConnectionsByDistance() const {
        std::cout << "\n=== Connections Sorted by Distance (Smallest to Largest) ===" << std::endl;
        std::cout << std::string(70, '-') << std::endl;

        std::vector<Connection> connections;

        // Collect all connections
        for (const auto& [area, edges] : adjacencyList) {
            for (const auto& edge : edges) {
                // Only add each connection once (area1 < area2 alphabetically)
                if (area < edge.destination) {
                    connections.emplace_back(area, edge.destination, edge.distance);
                }
            }
        }

        // Sort by distance (smallest to largest)
        std::sort(connections.begin(), connections.end());

        // Display sorted connections with visit order
        std::cout << std::setw(5) << "Order" << std::setw(30) << "Area 1" 
                  << std::setw(30) << "Area 2" << std::setw(10) << "Distance" << std::endl;
        std::cout << std::string(70, '-') << std::endl;

        for (size_t i = 0; i < connections.size(); ++i) {
            std::cout << std::setw(5) << (i + 1)
                      << std::setw(30) << connections[i].area1
                      << std::setw(30) << connections[i].area2
                      << std::setw(10) << std::fixed << std::setprecision(1) << connections[i].distance << " km" << std::endl;
        }
        std::cout << std::string(70, '-') << std::endl;
    }

    // Display visit order starting from a specific area, visiting smallest distances first
    void displayVisitOrderFromArea(const std::string& startArea) const {
        if (adjacencyList.find(startArea) == adjacencyList.end()) {
            std::cout << "Area " << startArea << " not found in graph." << std::endl;
            return;
        }

        std::cout << "\n=== Visit Order Starting from " << startArea << " ===" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        std::vector<std::string> visitedAreas;
        std::vector<std::pair<std::string, double>> visitOrder;
        
        visitedAreas.push_back(startArea);
        std::string currentArea = startArea;

        std::cout << "Step 1: Start at " << currentArea << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        int step = 2;

        // Visit neighbors in order of smallest distance first
        while (visitedAreas.size() < adjacencyList.size()) {
            const auto& edges = adjacencyList.at(currentArea);
            
            // Sort edges by distance
            std::vector<Edge> sortedEdges = edges;
            std::sort(sortedEdges.begin(), sortedEdges.end(),
                     [](const Edge& a, const Edge& b) { return a.distance < b.distance; });

            bool foundNext = false;

            // Find the nearest unvisited neighbor
            for (const auto& edge : sortedEdges) {
                if (std::find(visitedAreas.begin(), visitedAreas.end(), edge.destination) == visitedAreas.end()) {
                    std::cout << "Step " << step << ": Travel from " << currentArea << " to " << edge.destination 
                              << " (" << std::fixed << std::setprecision(1) << edge.distance << " km)" << std::endl;
                    
                    visitedAreas.push_back(edge.destination);
                    visitOrder.push_back({edge.destination, edge.distance});
                    currentArea = edge.destination;
                    foundNext = true;
                    step++;
                    break;
                }
            }

            if (!foundNext) {
                break;
            }
        }

        std::cout << std::string(80, '-') << std::endl;
        std::cout << "\nVisit Summary:" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        double totalDistance = 0.0;
        for (size_t i = 0; i < visitOrder.size(); ++i) {
            std::cout << (i + 1) << ". " << visitOrder[i].first 
                      << " (Distance: " << std::fixed << std::setprecision(1) << visitOrder[i].second << " km)" << std::endl;
            totalDistance += visitOrder[i].second;
        }

        std::cout << std::string(80, '-') << std::endl;
        std::cout << "Total areas visited: " << visitedAreas.size() << std::endl;
        std::cout << "Total distance traveled: " << std::fixed << std::setprecision(1) << totalDistance << " km" << std::endl;
        std::cout << std::endl;
    }

    // Find shortest path using Dijkstra's algorithm
    void findShortestPath(const std::string& startArea, const std::string& endArea) const {
        if (adjacencyList.find(startArea) == adjacencyList.end()) {
            std::cout << "Starting area " << startArea << " not found in graph." << std::endl;
            return;
        }
        if (adjacencyList.find(endArea) == adjacencyList.end()) {
            std::cout << "Ending area " << endArea << " not found in graph." << std::endl;
            return;
        }

        if (startArea == endArea) {
            std::cout << "\nStarting and ending areas are the same!" << std::endl;
            std::cout << "Distance: 0 km" << std::endl;
            return;
        }

        // Dijkstra's algorithm
        std::unordered_map<std::string, double> distances;
        std::unordered_map<std::string, std::string> previous;
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

        // Initialize distances
        for (const auto& [area, _] : adjacencyList) {
            distances[area] = std::numeric_limits<double>::infinity();
            previous[area] = "";
        }

        distances[startArea] = 0.0;
        pq.push(Node(startArea, 0.0));

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            // Skip if we've already found a better path
            if (current.distance > distances[current.area]) {
                continue;
            }

            // If we reached the end area, we can stop
            if (current.area == endArea) {
                break;
            }

            // Check all neighbors
            const auto& edges = adjacencyList.at(current.area);
            for (const auto& edge : edges) {
                double newDistance = distances[current.area] + edge.distance;

                if (newDistance < distances[edge.destination]) {
                    distances[edge.destination] = newDistance;
                    previous[edge.destination] = current.area;
                    pq.push(Node(edge.destination, newDistance));
                }
            }
        }

        // Reconstruct path
        std::vector<std::string> path;
        std::string current = endArea;

        if (distances[endArea] == std::numeric_limits<double>::infinity()) {
            std::cout << "\nNo path exists between " << startArea << " and " << endArea << std::endl;
            return;
        }

        while (!current.empty()) {
            path.push_back(current);
            current = previous[current];
        }

        std::reverse(path.begin(), path.end());

        // Display the shortest path
        std::cout << "\n=== Shortest Path from " << startArea << " to " << endArea << " ===" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << "Step " << (i + 1) << ": " << path[i];
            
            if (i < path.size() - 1) {
                double segmentDistance = getDistanceInternal(path[i], path[i + 1]);
                std::cout << " -> " << std::fixed << std::setprecision(1) << segmentDistance << " km";
            }
            std::cout << std::endl;
        }

        std::cout << std::string(80, '-') << std::endl;
        std::cout << "Total distance: " << std::fixed << std::setprecision(1) << distances[endArea] << " km" << std::endl;
        std::cout << "Total areas visited: " << path.size() << std::endl;
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
