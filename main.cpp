#include "graph.hpp"

int main() {
    // Create a graph of conservation areas
    Graph conservationNetwork;

    // Add conservation areas (nodes)
    conservationNetwork.addArea("Serengeti National Park");
    conservationNetwork.addArea("Masai Mara National Reserve");
    conservationNetwork.addArea("Amboseli National Park");
    conservationNetwork.addArea("Tsavo East National Park");
    conservationNetwork.addArea("Mount Kenya National Park");

    // Add connections between areas with distances in km
    conservationNetwork.addConnection("Serengeti National Park", "Masai Mara National Reserve", 150.5);
    conservationNetwork.addConnection("Masai Mara National Reserve", "Amboseli National Park", 200.0);
    conservationNetwork.addConnection("Amboseli National Park", "Tsavo East National Park", 280.3);
    conservationNetwork.addConnection("Tsavo East National Park", "Mount Kenya National Park", 220.7);
    conservationNetwork.addConnection("Mount Kenya National Park", "Serengeti National Park", 310.2);
    conservationNetwork.addConnection("Serengeti National Park", "Amboseli National Park", 450.0);

    // Display the entire graph as adjacency list
    conservationNetwork.displayGraph();

    // Display the graph as adjacency matrix
    conservationNetwork.displayAdjacencyMatrix();

    // Get neighbors of specific areas
    conservationNetwork.getNeighbors("Serengeti National Park");
    conservationNetwork.getNeighbors("Amboseli National Park");

    // Get distance between two areas
    double dist = conservationNetwork.getDistance("Serengeti National Park", "Masai Mara National Reserve");
    if (dist > 0) {
        std::cout << "\nDistance: " << dist << " km\n" << std::endl;
    }

    // Get statistics
    std::cout << "Total conservation areas: " << conservationNetwork.getNumberOfAreas() << std::endl;
    std::cout << "Total connections: " << conservationNetwork.getNumberOfConnections() << std::endl;

    return 0;
}
