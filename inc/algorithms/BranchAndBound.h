//
// Created by kacper on 25.10.2022.
//

#pragma once

#include "Algorithm.h"
#include <climits>

class BranchAndBound : public Algorithm {
    //Class variables
    size_t instanceSize{};

    int *currPath = nullptr;
    bool *visited = nullptr;
    int *optimalPath = nullptr;
    int optimalCost = INT_MAX;

    void setupVariables(const AdjacencyMatrix &graph); //initializes all class variables except optimalCost
    void resetVariables(); //deallocates memory used by class variables
    void copyToFinal(); //copies elements from currPath to optimalPath
    void TSPRec(AdjacencyMatrix &graph, int baseCost, int level); //implements TSP algorithm
    Path *createResultPath(); //creates Path object from optimalPath and optimalCost

public:
    //Calculates TSPRec result for graph and returns in Path object
    Path *execute(AdjacencyMatrix &graph) override;

    //Calculates TSPRec result for graph and returns nothing, used for time measurements
    void testExecute(AdjacencyMatrix &graph) override;
};