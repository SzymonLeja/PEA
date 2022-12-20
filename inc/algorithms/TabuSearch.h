//
// Created by kacpe on 01.12.2022.
//

#pragma once

#include <vector>
#include "Algorithm.h"

class TabuSearch : public Algorithm {
    const int iterationLimit;
    const int maxCacheSize;
    const int neighboursListSize;

    static int calculatePathCost(const AdjacencyMatrix &graph, const  DynamicArray<size_t> &vertices);
    static DynamicArray<size_t> getInitialPath(int instanceSize);
    static void swapRandomPair(DynamicArray<size_t> &vertices);
    static void swapPair(DynamicArray<size_t> &vertices, int firstIndex, int secondIndex);

    std::vector<DynamicArray<size_t>> generateNeighbours(DynamicArray<size_t> vertices) const;
    void updateCache(const DynamicArray<size_t> &currentPath, std::vector<DynamicArray<size_t>> &cache) const;

public:
    explicit TabuSearch(
            int iterationLimit = 10000,
            int maxCacheSize = 200,
            int neighboursListSize = 100
                    );

    void testExecute(AdjacencyMatrix &graph) override;

    Path *execute(AdjacencyMatrix &graph) override;
};