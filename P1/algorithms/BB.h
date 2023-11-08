//
// Created by stani on 14.10.2023.
//

#ifndef P1_BB_H
#define P1_BB_H


#include <stdlib.h>
#include <string>
using namespace std;


#include "../data_structures/Graph.h"
#include "../data_structures/Stack.h"


class BB {
public:
    int numOfCities;           // number of cities - nodes in graph
    vector<int> path;          // vector containing currently explored path
    vector<int> best_path;     // vector containing currently best path


    bool *visited;              // list of already visited cities
    int path_len = 0;           // length of path (number of already visited cities)
    int best_cost;              // minimal cost of checked paths (currently set as maximal integer value)
    int current_cost;           // cost of current path
    int **matrix;               // matrix containing cost of traveling between cities - weights of vertices
    int *cheapest_exit;         // helping array with the cheapest exit
    int lowerBound;             // value of lower bound for current branch

    void printResult();                // method for printing the result
    explicit BB(Graph graph);          //constructor
    void recursion(int vertex);        // main method for calculating the result
    int higherBound(int node);         // method for calculating the bound for current branch
    void findCheapest();               // method for finding the cheapest exits for each node
    void run();                        // method for running the algorithm, starts recursion for node 0 and prints result
    ~BB();

};



#endif //P1_BB_H
