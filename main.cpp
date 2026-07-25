#include "graph.hpp"
#include <iostream>
#include <limits>

void displayMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "    WILDLIFE CONSERVATION AREAS NETWORK" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "\n1. View all conservation areas" << std::endl;
    std::cout << "2. View neighboring parks for a specific area" << std::endl;
    std::cout << "3. View distance between two areas" << std::endl;
    std::cout << "4. View adjacency list representation" << std::endl;
    std::cout << "5. View adjacency matrix representation" << std::endl;
    std::cout << "6. View graph statistics" << std::endl;
    std::cout << "7. View all connections sorted by distance" << std::endl;
    std::cout << "8. View visit order from a specific area" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Enter your choice (1-9): ";
}

void displayAllAreas(const Graph& graph) {
    std::cout << "\n--- All Conservation Areas ---" << std::endl;
    std::cout << "1. Kruger National Park" << std::endl;
    std::cout << "2. Limpopo National Park" << std::endl;
    std::cout << "3. Hwange National Park" << std::endl;
    std::cout << "4. Chobe National Park" << std::endl;
    std::cout << "5. Etosha National Park" << std::endl;
    std::cout << "6. Kgalagadi Transfrontier Park" << std::endl;
    std::cout << "\nTotal areas in network: " << graph.getNumberOfAreas() << std::endl;
}

void viewNeighboringParks(const Graph& graph) {
    std::cout << "\n--- Select a Park to View Neighbors ---" << std::endl;
    std::cout << "1. Kruger National Park" << std::endl;
    std::cout << "2. Limpopo National Park" << std::endl;
    std::cout << "3. Hwange National Park" << std::endl;
    std::cout << "4. Chobe National Park" << std::endl;
    std::cout << "5. Etosha National Park" << std::endl;
    std::cout << "6. Kgalagadi Transfrontier Park" << std::endl;
    std::cout << "7. Back to main menu" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter your choice (1-7): ";

    int choice;
    std::cin >> choice;

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string selectedArea;
    switch (choice) {
        case 1:
            selectedArea = "Kruger National Park";
            break;
        case 2:
            selectedArea = "Limpopo National Park";
            break;
        case 3:
            selectedArea = "Hwange National Park";
            break;
        case 4:
            selectedArea = "Chobe National Park";
            break;
        case 5:
            selectedArea = "Etosha National Park";
            break;
        case 6:
            selectedArea = "Kgalagadi Transfrontier Park";
            break;
        case 7:
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            return;
    }

    graph.getNeighbors(selectedArea);
}

void viewDistanceBetweenAreas(const Graph& graph) {
    std::cout << "\n--- Select First Area ---" << std::endl;
    std::cout << "1. Kruger National Park" << std::endl;
    std::cout << "2. Limpopo National Park" << std::endl;
    std::cout << "3. Hwange National Park" << std::endl;
    std::cout << "4. Chobe National Park" << std::endl;
    std::cout << "5. Etosha National Park" << std::endl;
    std::cout << "6. Kgalagadi Transfrontier Park" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter your choice (1-6): ";

    int choice1;
    std::cin >> choice1;

    std::cout << "\n--- Select Second Area ---" << std::endl;
    std::cout << "1. Kruger National Park" << std::endl;
    std::cout << "2. Limpopo National Park" << std::endl;
    std::cout << "3. Hwange National Park" << std::endl;
    std::cout << "4. Chobe National Park" << std::endl;
    std::cout << "5. Etosha National Park" << std::endl;
    std::cout << "6. Kgalagadi Transfrontier Park" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter your choice (1-6): ";

    int choice2;
    std::cin >> choice2;

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string area1, area2;
    
    switch (choice1) {
        case 1: area1 = "Kruger National Park"; break;
        case 2: area1 = "Limpopo National Park"; break;
        case 3: area1 = "Hwange National Park"; break;
        case 4: area1 = "Chobe National Park"; break;
        case 5: area1 = "Etosha National Park"; break;
        case 6: area1 = "Kgalagadi Transfrontier Park"; break;
        default:
            std::cout << "Invalid choice for first area." << std::endl;
            return;
    }

    switch (choice2) {
        case 1: area2 = "Kruger National Park"; break;
        case 2: area2 = "Limpopo National Park"; break;
        case 3: area2 = "Hwange National Park"; break;
        case 4: area2 = "Chobe National Park"; break;
        case 5: area2 = "Etosha National Park"; break;
        case 6: area2 = "Kgalagadi Transfrontier Park"; break;
        default:
            std::cout << "Invalid choice for second area." << std::endl;
            return;
    }

    if (area1 == area2) {
        std::cout << "\nThe areas are the same. Distance: 0 km" << std::endl;
    } else {
        double distance = graph.getDistance(area1, area2);
        if (distance > 0) {
            std::cout << "\nDistance between " << area1 << " and " << area2 
                      << ": " << distance << " km" << std::endl;
        }
    }
}

void viewGraphStatistics(const Graph& graph) {
    std::cout << "\n--- Graph Statistics ---" << std::endl;
    std::cout << "Total conservation areas: " << graph.getNumberOfAreas() << std::endl;
    std::cout << "Total connections: " << graph.getNumberOfConnections() << std::endl;
    std::cout << "Graph type: Undirected, Weighted" << std::endl;
    std::cout << "Data structure: Adjacency List (with adjacency matrix support)" << std::endl;
}

void viewVisitOrderFromArea(const Graph& graph) {
    std::cout << "\n--- Select Starting Area for Visit Order ---" << std::endl;
    std::cout << "1. Kruger National Park" << std::endl;
    std::cout << "2. Limpopo National Park" << std::endl;
    std::cout << "3. Hwange National Park" << std::endl;
    std::cout << "4. Chobe National Park" << std::endl;
    std::cout << "5. Etosha National Park" << std::endl;
    std::cout << "6. Kgalagadi Transfrontier Park" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter your choice (1-6): ";

    int choice;
    std::cin >> choice;

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string selectedArea;
    switch (choice) {
        case 1:
            selectedArea = "Kruger National Park";
            break;
        case 2:
            selectedArea = "Limpopo National Park";
            break;
        case 3:
            selectedArea = "Hwange National Park";
            break;
        case 4:
            selectedArea = "Chobe National Park";
            break;
        case 5:
            selectedArea = "Etosha National Park";
            break;
        case 6:
            selectedArea = "Kgalagadi Transfrontier Park";
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            return;
    }

    graph.displayVisitOrderFromArea(selectedArea);
}

int main() {
    // Create a graph of conservation areas
    Graph conservationNetwork;

    // Add conservation areas (nodes)
    conservationNetwork.addArea("Kruger National Park");
    conservationNetwork.addArea("Limpopo National Park");
    conservationNetwork.addArea("Hwange National Park");
    conservationNetwork.addArea("Chobe National Park");
    conservationNetwork.addArea("Etosha National Park");
    conservationNetwork.addArea("Kgalagadi Transfrontier Park");

    // Add connections between areas with distances in km
    conservationNetwork.addConnection("Kruger National Park", "Limpopo National Park", 280.0);
    conservationNetwork.addConnection("Limpopo National Park", "Hwange National Park", 250.0);
    conservationNetwork.addConnection("Hwange National Park", "Chobe National Park", 177.0);
    conservationNetwork.addConnection("Chobe National Park", "Etosha National Park", 1030.0);
    conservationNetwork.addConnection("Etosha National Park", "Kgalagadi Transfrontier Park", 1211.0);
    conservationNetwork.addConnection("Kgalagadi Transfrontier Park", "Kruger National Park", 1430.0);

    std::cout << "\n*** Network initialization complete ***\n" << std::endl;

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                displayAllAreas(conservationNetwork);
                break;

            case 2:
                viewNeighboringParks(conservationNetwork);
                break;

            case 3:
                viewDistanceBetweenAreas(conservationNetwork);
                break;

            case 4:
                conservationNetwork.displayGraph();
                break;

            case 5:
                conservationNetwork.displayAdjacencyMatrix();
                break;

            case 6:
                viewGraphStatistics(conservationNetwork);
                break;

            case 7:
                conservationNetwork.displayConnectionsByDistance();
                break;

            case 8:
                viewVisitOrderFromArea(conservationNetwork);
                break;

            case 9:
                std::cout << "\nThank you for using the Wildlife Conservation Areas Network!" << std::endl;
                std::cout << "Goodbye!" << std::endl;
                running = false;
                break;

            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 9." << std::endl;
        }
    }

    return 0;
}
