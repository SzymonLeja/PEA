//
// Created by kacper on 31.10.2022.
//

#include "../../inc/algorithms/DynamicProgramming.h"
#include <cmath>

void DynamicProgramming::setupVariables(const AdjacencyMatrix &graph) {
    //Setting instance size based on number of vertices in the graph
    instanceSize = graph.getCitiesNumber();

    //Setting numOfPaths based on size of the tree for instanceSize
    numOfPaths = int(pow(2, (double) instanceSize) - 1);

    //Initializing state 2d table
    state = new dpResult *[instanceSize];
    for (int i = 0; i < instanceSize; i++) {
        state[i] = new dpResult[numOfPaths];
    }
}

void DynamicProgramming::resetState() {
    for (int i = 0; i < instanceSize; i++) {
        delete[] state[i];
    }
    delete[] state;
}

dpResult DynamicProgramming::TSPRec(AdjacencyMatrix &graph, int currVertex, int visitedMask) {
    //Checking whether all vertices are visited at this point
    if (visitedMask == numOfPaths) {
        return {graph.getCost(currVertex, 0), currVertex}; // return to starting city
    }

    //Checking whether path for this mask was already calculated
    if (state[currVertex][visitedMask].cost != INT_MAX) {
        return state[currVertex][visitedMask];
    }

    for (int i = 0; i < instanceSize; ++i) {
        //Checking whether i is not the current vertex and whether it was not visited
        if (i == currVertex || (visitedMask & (1 << i))) {
            continue;
        }

        //Finding the best path from current vertex
        auto result = TSPRec(graph, i, visitedMask | (1 << i));

        //Adding cost of edge going from current vertex to i
        result.cost += graph.getCost(currVertex, i);

        //Adding currVertex to begging of the path
        result.path.addFront(currVertex);

        //Checking whether result of the path is better
        // than the optimal result for this vertex and mask
        // stored in state table
        if (result.cost < state[currVertex][visitedMask].cost) {
            //Updating state table result's cost and path
            state[currVertex][visitedMask].cost = result.cost;

            state[currVertex][visitedMask].path.clear();
            for (int it = 0; it < result.path.getSize(); it++) {
                state[currVertex][visitedMask].path.addBack(result.path[it]);
            }
        }
    }

    return state[currVertex][visitedMask];
}

Path *DynamicProgramming::createResultPath() {
    Path *result = new Path;

    for (int i = 0; i <= instanceSize; i++) {
        if (i == instanceSize) {
            result->addVertex(0);
            continue;
        }

        result->addVertex(state[0][1].path.at(i));
    }

    result->setCost(state[0][1].cost);

    return result;
}


Path *DynamicProgramming::execute(AdjacencyMatrix &graph) {
    setupVariables(graph);

    //Calculating optimal result
    dpResult result = TSPRec(graph, 0, 1);

    //Creating Path object from result
    auto path = createResultPath();

    resetState();

    return path;
}

void DynamicProgramming::testExecute(AdjacencyMatrix &graph) {
    setupVariables(graph);

    //Calculating optimal result
    dpResult result = TSPRec(graph, 0, 1);

    resetState();
}
