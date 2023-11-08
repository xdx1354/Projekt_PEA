//
// Created by stani on 14.10.2023.
//

#ifndef P1_BF_H
#define P1_BF_H
#include <stdlib.h>
#include <string>
using namespace std;


#include "../data_structures/Graph.h"
#include "../data_structures/Stack.h"


class BF {
public:
    int numOfCities;           // number of cities - nodes in graph
    vector<int> path;          // vector containing currently explored path
    vector<int> best_path;     // vector containing currently best path

    bool *visited;              // list of already visited cities
    int path_len = 0;           // length of path (number of already visited cities)
    int best_cost;              // minimal cost of checked paths (currently set as maximal integer value)
    int current_cost;           // cost of current path
    int **matrix;               // matrix containing cost of traveling between cities - weights of vertices

    void printResult();             // method for printing the result
    explicit BF(Graph graph);       // constructor of class
    void recursion(int node);       // main method for calculating the result
    void run();                     // method for running the algorithm, starts recursion for node 0 and prints result
    ~BF();                          // destructor
};


#endif //P1_BF_H