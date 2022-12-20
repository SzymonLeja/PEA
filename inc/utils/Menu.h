//
// Created by kacper on 02.11.2022.
//

#pragma once

#include "../containers/AdjacencyMatrix.h"
#include "../algorithms/Algorithm.h"
#include "Enums.h"

class Menu {
    //Class variables
    static AdjacencyMatrix *graph;

public:
    static void initMenu(); //display initial menu
    static void tsp1Menu();
    static void tsp2Menu();

    static void readGraph(); //display graph creation wizard
    static void generateGraph(); //display random graph generation wizard
    static void displayGraph();

    static void runAlgorithm(Algorithms algorithm); //run chosen algorithm and display result
};