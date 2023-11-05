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
    int numOfVertices;
    int result;
    int temp;
    int **dp;
    int **history;
    int lastVertex;

public:
    void apply();
    std::string resultToString();
    void printResult();
    DP(Graph graph);
    void run();
    ~DP();
};



#endif //P1_DP_H
