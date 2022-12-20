//
// Created by kacper on 21.10.2022.
//
#include "../../inc/algorithms/BruteForce.h"
#include <algorithm>

void BruteForce::fillBuffer(size_t verticesNumber) {
    for (int index = 0; index < verticesNumber; ++index) {
        permutationBuffer.addBack(index);
    }

    optimalCost = INT_MAX;
}

void BruteForce::resetVariables() {
    permutationBuffer.clear();
    optimalPath.clear();
    optimalCost = INT_MAX;
}

int BruteForce::calculateCost(const AdjacencyMatrix &matrix) {
    int totalCost = 0;
    auto lastIndex = permutationBuffer.getSize() - 1;

    for (int index = 0; index < lastIndex; index++) {
        totalCost += matrix.getCost(permutationBuffer[index], permutationBuffer[index + 1]);
    }

    totalCost += matrix.getCost(permutationBuffer[lastIndex], permutationBuffer[0]);

    return totalCost;
}

void BruteForce::reassignOptimalValues(int newOptimaCost) {
    optimalPath.clear();
    for (int i = 0; i < permutationBuffer.getSize(); i++) {
        optimalPath.addBack(permutationBuffer.at(i));
    }
    optimalPath.addBack(0);

    optimalCost = newOptimaCost;
}

Path *BruteForce::execute(AdjacencyMatrix &graph) {
    //Initialize permutation buffer
    fillBuffer(graph.getCitiesNumber());

    do {
        //Get path cost for current permutation
        auto currentCost = calculateCost(graph);

        //Checking whether cost is better than optimal
        if (currentCost < optimalCost) {
            reassignOptimalValues(currentCost);
        }
    } while (std::next_permutation(permutationBuffer.begin() + 1, permutationBuffer.end()));

    auto result = new Path(optimalPath, optimalCost);
    resetVariables();

    return result;
}

void BruteForce::testExecute(AdjacencyMatrix &graph) {
    //Initialize permutation buffer
    fillBuffer(graph.getCitiesNumber());

    do {
        //Get path cost for current permutation
        auto currentCost = calculateCost(graph);

        //Checking whether cost is better than optimal
        if (currentCost < optimalCost) {
            reassignOptimalValues(currentCost);
        }
    } while (std::next_permutation(permutationBuffer.begin() + 1, permutationBuffer.end()));

    resetVariables();
}
