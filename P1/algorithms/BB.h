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
#include "../data_structures/MyStack.h"


class BB {
public:
    int numOfCities;
    MyStack path;          // vector containing currently explored path
    MyStack best_path;     // vector containing currently best path

    bool *visited;
    int path_len = 0;           // length of path (number of already visited cities)
    int best_cost;              // minimal cost of checked paths (currently set as maximal integer value)
    int current_cost;           // cost of current path
    int **matrix;
    int *cheapest_exit;         // helping array with the cheapest exit
    int lowerBound;

    void printResult();
    explicit BB(Graph graph);        //constructor
    void recursion(int vertex);
    int higherBound(int node);
    void findCheapest();
    void run();
    ~BB();

};



#endif //P1_BB_H
