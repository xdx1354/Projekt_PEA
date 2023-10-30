//
// Created by stani on 25.10.2023.
//

#ifndef P1_MENU_H
#define P1_MENU_H


#include "../data_structures/Graph.h"

class Menu {
public:

    Graph g;
    void start();

    void run_BB();

    void run_BF();

    void run_DP();

    void measure_time();
};


#endif //P1_MENU_H
