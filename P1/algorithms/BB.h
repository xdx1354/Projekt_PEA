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

//TODO: redesign using self-made data structures

class BB {
public:
    int numOfCities;
    Stack path;          // vector containing currently explored path
    Stack best_path;     // vector containing currently best path

    bool *visited;
    int path_len = 0;           // length of path (number of already visited cities)
    int best_cost;              // minimal cost of checked paths (currently set as maximal integer value)
    int current_cost;           // cost of current path
    int **matrix;
    int *cheapest_entrance;     // helping array with the cheapest entrance to each node
    int *cheapest_exit;         // ...with the cheapest exit
    int lowerBound;

    void print();
    explicit BB(Graph graph);        //constructor
    void recursion(int vertex);
    int higherBound(int node);
    void findCheapest();
};



#endif //P1_BB_H
