//
// Created by kacper on 21.10.2022.
//

#pragma once

#include "Algorithm.h"
#include <climits>

class BruteForce : public Algorithm {
    //Class variables
    DynamicArray<int> permutationBuffer;
    DynamicArray<int> optimalPath;
    int optimalCost = INT_MAX;

    void fillBuffer(size_t verticesNumber); //fills buffer with vertices indexes
    void resetVariables();

    int calculateCost(const AdjacencyMatrix &matrix); //calculates path cost for current buffer state
    void reassignOptimalValues(int newOptimaCost); //reassigns optimalPath and optimalCost

public:
    //Calculates TSPRec result for graph and returns in Path object
    Path *execute(AdjacencyMatrix &graph) override;

    //Calculates TSPRec result for graph and returns nothing, used for time measurements
    void testExecute(AdjacencyMatrix &graph) override;
};
