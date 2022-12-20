//
// Created by kacpe on 29.11.2022.
//

#pragma once

#include "Algorithm.h"
#include <cstring>
#include <vector>

class SimulatedAnnealing {
    const double heat;
    const double coolingRate;
    DynamicArray<int> bestSolution;
    int bestCost;

    static int calculateCost(AdjacencyMatrix &graph, DynamicArray<int> &vertices);
    static bool makeDecision(int delta, double temperature);
    static void fullShuffle(DynamicArray<int> &vertices);
    static void quickShuffle(DynamicArray<int> &vertices);
    void fourShuffle(DynamicArray<int> &vertices);
    void shuffleRoadBetweenTwoVertices(DynamicArray<int> &vertices);

public:
    explicit SimulatedAnnealing(double heat = 1000, double coolingRate = 0.999);

    Path *execute(AdjacencyMatrix &matrix, std::string shuffleType=std::string("quick"), std::string coolingType=std::string("geometric"), int epochs=1);
    void testExecute(AdjacencyMatrix &matrix);
};