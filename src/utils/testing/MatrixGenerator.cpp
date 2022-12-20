//
// Created by kacper on 03.11.2022.
//

#include "../../../inc/utils/testing/MatrixGenerator.h"
#include <random>

AdjacencyMatrix *MatrixGenerator::graph = nullptr;

void MatrixGenerator::createGraph(int instanceSize, int costRange) {
    //Deleting old graph
    delete graph;

    //Creating new 2d table with costs
    int **distances = new int *[instanceSize];
    for (int i = 0; i < instanceSize; i++) {
        distances[i] = new int[instanceSize];
    }

    //Setting up  cost generating
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> range(1, costRange);

    //Filling base array with random costs
    for (int i = 0; i < instanceSize; i++) {
        for (int j = 0; j < instanceSize; j++) {

            //Creating matrix diagonal
            if (j == i) {
                distances[i][j] = -1;
                continue;
            }

            distances[i][j] = range(gen);
        }
    }

    graph = new AdjacencyMatrix(instanceSize, distances);
}
