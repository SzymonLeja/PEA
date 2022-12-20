//
// Created by kacper on 31.10.2022.
//

#pragma once

#include "Algorithm.h"
#include <climits>

//Structure used to pass optimal path and cost
// from lower to upper levels of recursive function TSPRec
struct dpResult {
    //Struct variables
    int cost;
    DynamicArray<int> path;

    dpResult(int cost, int firstVertex) {
        this->cost = cost;
        path.addBack(firstVertex);
    };

    dpResult() {
        this->cost = INT_MAX;
    };

};

class DynamicProgramming : public Algorithm {
    //Class variables
    size_t instanceSize{};
    size_t numOfPaths{};
    dpResult **state{};

    void setupVariables(const AdjacencyMatrix &graph); //initializes all class variables
    void resetState(); //deallocates memory used by state table
    dpResult TSPRec(AdjacencyMatrix &graph, int currVertex, int visitedMask); //implements TSP algorithm
    Path *createResultPath(); //creates Path object from optimalPath and optimalCost

public:
    //Calculates TSPRec result for graph and returns in Path object
    Path *execute(AdjacencyMatrix &graph) override;

    //Calculates TSPRec result for graph and returns nothing, used for time measurements
    void testExecute(AdjacencyMatrix &graph) override;
};


