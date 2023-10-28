//
// Created by stani on 15.10.2023.
//

#ifndef P1_DP_H
#define P1_DP_H


#include "../data_structures/Graph.h"

class DP {

private:

    int **matrix;
    int numOfCities;
    int **dp;

public:
    int apply();
    std::string toString();



    DP(Graph graph);
};


#endif //P1_DP2_H
