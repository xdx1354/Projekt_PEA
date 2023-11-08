//
// Created by stani on 28.10.2023.
//

#ifndef P1_DP_H
#define P1_DP_H

#include "../data_structures/Graph.h"

#define INF 9999
using namespace std;

class DP
{
private:
    int **matrix;               // matrix containing cost of traveling between cities - weights of vertices
    int numOfCities;            // number of cities - nodes in graph
    int result;                 // result of the algorithm - cost of min Hamiltonian path
    int **dp;                   // array for storing calculated data in process of dynamic programming
    int **history;              // array that will help with retrieving the shortest path
    int lastVertex;             // last vertex of current path

public:
    void apply();               // main method for calcualting the result
    string resultToString();    // method returning result as string
    void printResult();         // method for printing the result
    void run();                 // method for running the algorithm
    DP(Graph graph);            // constructor
    ~DP();                      // destructor
};



#endif //P1_DP_H
