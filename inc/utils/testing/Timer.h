//
// Created by kacper on 21.10.2022.
//

#pragma once

#include "../Enums.h"
#include <chrono>

class Timer {
    //Class variables
    bool isStarted = false;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

public:
    void start(); //initialize startTime and isStarted members

    double getTime(TimeUnit unit); //negate isStarted and get interval between now and startTime in desired unit
};
