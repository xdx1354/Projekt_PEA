//
// Created by stani on 25.10.2023.
//

#ifndef P1_MENU_H
#define P1_MENU_H

#include "../data_structures/Graph.h"

class Menu {
public:

    Graph g;                        // Object of class graph, it will contain currently used graph
    void start();                   // starts the menu

    void runTS(int, float, float);  // runs Tabu Search algorithm

    void runGenetic(int endCon, int crossCount, int mutateCount, int crossCount2, int mutateCount2,  int sizeOfPopulation);
};


#endif //P1_MENU_H
