//
// Created by kacpe on 05.12.2022.
//

#pragma once

#include <list>
#include "../../containers/AdjacencyMatrix.h"
#include "../Enums.h"

struct Instance {
    AdjacencyMatrix graph;
    std::string name;
};

struct ErrorResult {
    double avgTime;
    double avgResult;
    std::string instanceName;
};

class ErrorTests {
    std::list <Instance> instances;
    std::list<ErrorResult> saResults;
    std::list<ErrorResult> tsResults;

    static double calcAvg(const std::list<double> &); //Calculate average time from list elements
    static double calcAvg(const std::list<int> &); //Calculate average time from list elements

    void loadInstances();
    void addSeriesAvg(double avgTime, double avgError, std::string instanceName, Algorithms alg);
    void saveResultList(const std::string &algorithm, Algorithms alg) const; //Save results an algorithm to file

public :
    size_t sampleSize = 100;
    std::string outputPath = "Error_tests\\";
    std::string inputPath = "input//";

    void testAll();
    void testSA();
    void testTS();
};



