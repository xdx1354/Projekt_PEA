//
// Created by stani on 28.10.2023.
//

#ifndef P1_DP_H
#define P1_DP_H

#include "../data_structures/Graph.h"

#define INF 9999

class DP
{
private:
    int **matrix;
    int count;
    int result;
    int temp;
    int **memory;
    int **getMemory;
    int lastVertex;

public:
    void apply();
    std::string toString();
    int getResult();
    DP(Graph graph);
    ~DP();
};



#endif //P1_DP_H
