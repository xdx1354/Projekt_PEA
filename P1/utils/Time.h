//
// Created by stani on 24.05.2023.
//

#ifndef PROJEKT2_TIME_H
#define PROJEKT2_TIME_H

#include "iostream"
#include "chrono"
using namespace  std;
using namespace std::chrono;

class Time {
public:

    high_resolution_clock::time_point startPoint;               // time stamp of starting time

    high_resolution_clock::time_point stopPoint;                // time stamp for ending time

    void start();                                               // makes time stamp for start
    void stop();                                                // make time stamp for end
    long long returnTime();                                     // calculates elapsed time
};


#endif //PROJEKT2_TIME_H
