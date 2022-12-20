//
// Created by kacper on 02.11.2022.
//

//#include <cstdlib>
#include <iostream>
#include "../../inc/utils/Menu.h"
#include "../../inc/algorithms/BruteForce.h"
#include "../../inc/algorithms/DynamicProgramming.h"
#include "../../inc/algorithms/BranchAndBound.h"
#include "../../inc/utils/FileManager.h"
#include "../../inc/utils/testing/MatrixGenerator.h"
#include "../../inc/algorithms/SimulatedAnnealing.h"
#include "../../inc/algorithms/TabuSearch.h"

AdjacencyMatrix *Menu::graph = nullptr;

void Menu::readGraph() {
    system("cls");
    std::string fileName;

    std::cout << "Enter name of the file eg. \"data.txt\"\n(must be located in the same directory as .exe file): ";
    std::cin >> fileName;

    FileManager::readData(fileName);

    if (FileManager::data == nullptr) {
        system("cls");

        std::cout << "File not found!\n";
        system("Pause");
        return;
    }

    delete graph;
    graph = new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
}

void Menu::generateGraph() {
    system("cls");
    std::string size;

    std::cout << "Enter size of the graph (If graph is already read, it will be overwritten!): ";
    std::cin >> size;

    try {
        auto graphSize = std::stoi(size);

        if (graphSize <= 0) {
            system("cls");
            std::cout << "Provided size must be greater than 0!\n";
            system("Pause");
        }

        MatrixGenerator::createGraph(graphSize);
        graph = MatrixGenerator::graph;

    } catch (std::exception &e) {
        system("cls");
        std::cout << "Provided size is not a number!\n";
        system("Pause");
    }
}

void Menu::displayGraph() {
    system("cls");

    if (graph == nullptr) {
        std::cout << "Please read graph first!\n";
        system("Pause");

        return;
    }

    graph->print();

    std::cout << std::endl;
    system("Pause");
}

void Menu::initMenu() {
    //Displaying initial menu with available options
    char input;

    while (true) {
        system("cls");

        std::cout << "[0] TSP1\n";
        std::cout << "[1] TSP2\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                tsp1Menu();
                break;
            case '1':
                tsp2Menu();
                break;
            case 'Q':
                return;
            case 'q':
                return;

            default:
                break;
        }
    }
}

void Menu::tsp1Menu() {
//Displaying initial menu with available options
    char input;

    while (true) {
        system("cls");

        std::cout << "[0] Read graph\n";
        std::cout << "[1] Generate random graph\n";
        std::cout << "[2] Display graph\n";
        std::cout << "[3] Brute force\n";
        std::cout << "[4] Dynamic programming\n";
        std::cout << "[5] Branch and bound\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                readGraph();
                break;
            case '1':
                generateGraph();
                break;
            case '2':
                displayGraph();
                break;
            case '3':
                runAlgorithm(Algorithms::BF);
                break;
            case '4':
                runAlgorithm(Algorithms::DP);
                break;
            case '5':
                runAlgorithm(Algorithms::BB);
                break;
            case 'Q':
                return;
            case 'q':
                return;

            default:
                break;
        }
    }
}

void Menu::tsp2Menu() {
//Displaying initial menu with available options
    char input;

    while (true) {
        system("cls");

        std::cout << "[0] Read graph\n";
        std::cout << "[1] Generate random graph\n";
        std::cout << "[2] Display graph\n";
        std::cout << "[3] Simulated annealing\n";
        std::cout << "[4] Tabu search\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                readGraph();
                break;
            case '1':
                generateGraph();
                break;
            case '2':
                displayGraph();
                break;
            case '3':
                runAlgorithm(Algorithms::SA);
                break;
            case '4':
                runAlgorithm(Algorithms::TS);
                break;
            case 'Q':
                return;
            case 'q':
                return;

            default:
                break;
        }
    }
}

void Menu::runAlgorithm(Algorithms algorithm) {
    system("cls");

    if (graph == nullptr) {
        std::cout << "Please read graph first!\n";
        system("Pause");

        return;
    }

    BruteForce bfEntity;
    DynamicProgramming dpEntity;
    BranchAndBound bbEntity;
    SimulatedAnnealing saEntity;
    TabuSearch tsEntity;

    switch (algorithm) {
        case BF:
            std::cout << bfEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;

        case DP:
            std::cout << dpEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;

        case BB:
            std::cout << bbEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;
        case SA:
            std::cout << saEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;
        case TS:
            std::cout << tsEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;
    }
}