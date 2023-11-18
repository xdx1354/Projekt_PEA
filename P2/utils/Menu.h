//
// Created by stani on 25.10.2023.
//

#ifndef P1_MENU_H
#define P1_MENU_H


#include "../data_structures/Graph.h"

class Menu {
public:

    Graph g;                    // Object of class graph, it will contain currently used graph
    void start();               // starts the menu

    void run_BB();              // runs Branch and Bound algorithm for graph

    void run_BF();              // runs Brut Force algorithm for graph

    void run_DP();              // runs Dynamic Programming algorithm for graph

};


#endif //P1_MENU_H
