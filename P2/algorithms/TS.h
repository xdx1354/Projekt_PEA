//
// Created by stani on 18.11.2023.
//

#ifndef P1_TS_H
#define P1_TS_H
using namespace std;
#include "../data_structures/Graph.h"

class TS {


public:
    TS(Graph graph);
    void apply(int maxIterations);               // running the algorithm, preparing var and objects
    int* generateFirstPath();   // generates initial path with selected method  // TODO: can be void if data will be passed directly to field of class
    void generateNeighbourPath();    // generates path using certain method (swaps etc. TODO: decide on a method)
    void epoch();               // loop method, loop for set times and tries to calculate the most optimal res
    int calculatePathCost(int path[]);   // for a given path calculates it cost
    bool findInTabu(int path[]);          // checks if given path is present in tabu list


    ///COMMENTS
    // Paths will be stored as dynamic arrays
    // Moze nalez stworzyć klase Path???

    // fields

    Graph g;
    int numOfCities;                   // size of the graph
    int *bestPath;              // stores the best already found path, should be initialized with all -1?
    int bestPathCost = INT_MAX;
    int *currentPath;           // stores currently calculated path
    int currentPathCost = INT_MAX;
    int *neighbourPath;
    int neighbourPathCost = INT_MAX;
    int endCondition;
    int **matrix;               // extracting the matrix from graph class to have more convenient access
    int **tabulist;
    int tabulistLength;

};


#endif //P1_TS_H
