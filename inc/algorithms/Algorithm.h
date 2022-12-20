//
// Created by kacper on 21.10.2022.
//

#pragma once

#include "../containers/AdjacencyMatrix.h"
#include "../containers/Path.h"

class Algorithm {
    virtual Path *execute(AdjacencyMatrix &graph) = 0; //returns result
    virtual void testExecute(AdjacencyMatrix &graph) = 0; //returns void, used for testing
};
