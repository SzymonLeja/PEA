//
// Created by kacper on 25.10.2022.
//
#include "../../inc/algorithms/BranchAndBound.h"

void BranchAndBound::setupVariables(const AdjacencyMatrix &graph) {
    //Setting instance size based on number of vertices in the graph
    instanceSize = graph.getCitiesNumber();

    //Initializing tables with zeroes
    currPath = new int[graph.getCitiesNumber() + 1]{};
    visited = new bool[graph.getCitiesNumber()]{};
    optimalPath = new int[graph.getCitiesNumber() + 1]{};
}

void BranchAndBound::resetVariables() {
    delete[] currPath;
    delete[] visited;
    delete[] optimalPath;
}

void BranchAndBound::copyToFinal() {
    //Copying elements from current path to optimal path
    for (int i = 0; i <= instanceSize; i++) {
        if (i == instanceSize) {
            optimalPath[instanceSize] = currPath[0];
            continue;
        }

        optimalPath[i] = currPath[i];
    }
}

void BranchAndBound::TSPRec(AdjacencyMatrix &graph, int baseCost, int level) {
    //Checking whether all vertices are visited at this point
    if (level == instanceSize) {

        //Checking whether there is an edge from current vertex to starting vertex
        if (graph.getCost(currPath[level - 1], currPath[0]) > 0) {

            int totalCost = baseCost + graph.getCost(currPath[level - 1], currPath[0]);

            //Update optimalPath and optimalCost if current total cost is better
            if (totalCost < optimalCost) {
                copyToFinal();
                optimalCost = totalCost;
            }
        }

        return;
    }

    //Iterating through every vertex to build search tree for every other level
    for (int i = 0; i < instanceSize; i++) {
        int currEdgeCost = graph.getCost(currPath[level - 1], i);

        //Checking whether curr edge exists and whether vertex was not visited yet
        if (currEdgeCost <= 0 || visited[i]) {
            continue;
        }

        //Checking whether path from current vertex is worth exploring
        //based on the fact whether curr total cost is smaller than optimal cost
        if (baseCost + currEdgeCost >= optimalCost) {
            continue;
        }

        //Adding current vertex to current path and marking it visited
        currPath[level] = i;
        visited[i] = true;

        //Going down the path from current vertex
        TSPRec(graph, baseCost + currEdgeCost, level + 1);


        //Resetting visited table after exploring path from current vertex
        delete[] visited;
        visited = new bool[instanceSize]{};

        for (int j = 0; j <= level - 1; j++) {
            visited[currPath[j]] = true;
        }
    }
}

Path *BranchAndBound::createResultPath() {
    Path *result = new Path;

    for (int i = 0; i <= instanceSize; i++) {
        if (i == instanceSize) {
            result->addVertex(optimalPath[instanceSize]);
            continue;
        }

        result->addVertex(optimalPath[i]);
    }

    result->setCost(optimalCost);

    return result;
}

Path *BranchAndBound::execute(AdjacencyMatrix &graph) {
    setupVariables(graph);

    //Marking vertex 0 as visited since it is a starting vertex
    visited[0] = true;

    //Calculating optimal cost and path
    TSPRec(graph, 0, 1);

    //Creating result Path object
    auto resultPath = createResultPath();

    resetVariables();

    return resultPath;
}

void BranchAndBound::testExecute(AdjacencyMatrix &graph) {
    setupVariables(graph);

    //Marking vertex 0 as visited since it is a starting vertex
    visited[0] = true;

    //Calculating optimal cost and path
    TSPRec(graph, 0, 1);

    resetVariables();
}