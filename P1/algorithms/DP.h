//
// Created by stani on 15.10.2023.
//

#ifndef P1_DP_H
#define P1_DP_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <stack>
#include "../data_structures/Graph.h"


using namespace std;

class DP {
public:

    Graph g;
    int **cost;
    int n;
    int result;
    int temp;
    int **dp;
    int **parent;
    int lastVertex;


    int heldKarp(int current, int visited);

    void printTour(int startCity);
    DP();
};


#endif //P1_DP_H
