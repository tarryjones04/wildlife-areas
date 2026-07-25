#include "graph.hpp"

int main() {
    // Create a graph of conservation areas
    Graph conservationNetwork;

    // Add conservation areas (nodes)
    conservationNetwork.addArea("Kruger National Park");
    conservationNetwork.addArea("Limpopo National Park");
    conservationNetwork.addArea("Hwange National Park");
    conservationNetwork.addArea("Etosha National Park");
    conservationNetwork.addArea("Kgalagadi Transfrontier Park");

    // Add connections between areas with distances in km
    conservationNetwork.addConnection("Kruger National Park", "Limpopo National Park", 280.0);
    conservationNetwork.addConnection("Limpopo National Park", "Hwange National Park",250.0 );
    conservationNetwork.addConnection("Hwange National Park", "Chobe National Park", 177.0);
    conservationNetwork.addConnection("Chobe National Park", "Etosha National Park", 1030.0);
    conservationNetwork.addConnection("Etosha National Park", "Kgalagadi Transfrontier Park", 1211.0);
    conservationNetwork.addConnection("Kgalagadi Transfrontier Park", "Kruger National Park",1430.0 );

    // Display the entire graph as adjacency list
    conservationNetwork.displayGraph();

    // Display the graph as adjacency matrix
    conservationNetwork.displayAdjacencyMatrix();

    // Get neighbors of specific areas
    conservationNetwork.getNeighbors("Kruger National Park");
    conservationNetwork.getNeighbors("Chobe National Park");

    // Get distance between two areas
    double dist = conservationNetwork.getDistance("Kruger National Park", "Limpopo National Reserve");
    if (dist > 0) {
        std::cout << "\nDistance: " << dist << " km\n" << std::endl;
    }

    // Get statistics
    std::cout << "Total conservation areas: " << conservationNetwork.getNumberOfAreas() << std::endl;
    std::cout << "Total connections: " << conservationNetwork.getNumberOfConnections() << std::endl;

    return 0;
}
