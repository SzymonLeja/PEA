//
// Created by kacpe on 04.11.2022.
//

#pragma once

#include "../../containers/AdjacencyMatrix.h"
#include "../Enums.h"
#include "Timer.h"
#include <list>
#include <string>

//Helping structure for individual results
struct TimeResult {
    double time;
    size_t instanceSize;
};


class TimeTests {
    //Class variables
    static AdjacencyMatrix *graph;

    Timer timer;
    std::list<TimeResult> bfResults;
    std::list<TimeResult> dpResults;
    std::list<TimeResult> bbResults;
    std::list<TimeResult> saResults;
    std::list<TimeResult> tsResults;

    void saveResultList(const std::string &algorithm, Algorithms alg) const; //Save results an algorithm to file
    void addSeriesAvg(double avg, int instanceSize, Algorithms alg); //Add avg time to adequate result list
    static double calcAvg(const std::list<double> &); //Calculate average time from list elements

public:
    size_t sampleSize = 100;
    int costRange = 100;
    std::string basePath = "TimeTests\\";

    //Class methods
    void testAll(int start, int end); //Perform testing for all algorithms in matrix representation
    void testBB(int start, int end);
    void testDP(int start, int end);
    void testBF(int start, int end);
    void testSA(int start, int end, int jump);
    void testTS(int start, int end, int jump);
};