//
// Created by stani on 14.10.2023.
//

#ifndef P1_BF_H
#define P1_BF_H
#include <stdlib.h>
#include <string>


#include "../data_structures/Graph.h"
#include "../data_structures/Stack.h"

class BF {
public:
    int numOfCities;
    Stack path;
    bool *visited;
    int path_len;           // length of path (number of already visited cities)
    int best_cost;           // minimal cost of checked paths (currently set as maximal integer value)
    int current_cost;       // cost of current path
    int startingCity = 0;   // the algo will always start from city number 0

    void brut_force(Graph graph);
    void hamiltonian_path(int v, Graph graph);


};


#endif //P1_BF_H
