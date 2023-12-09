//
// Created by stani on 18.11.2023.
//

#ifndef P1_TS_H
#define P1_TS_H
using namespace std;
#include "../data_structures/Graph.h"
#include "../data_structures/MoveQueue.h"

/**
 * Tabu Search algorithm at first generates a base, starting result and than new neighbour results by swapping some cities
 * (to in each step). If result is better then current one, it will be expanded. Also to prevent coming to previous res
 * there is a tabu list of forbidden steps which will help avoid being stuck in local optimum. The point of algo is to
 * sometimes take worse result and expand it, in order to quit local optimum.
 */
class TS {


public:
    TS(Graph graph);
    void apply(int endCondition, float, float);          // running the algorithm, preparing var and objects
    void generateFirstPath();               // generates initial path with selected method  // TODO: can be void if data will be passed directly to field of class
    void generateNeighbourPath();           // generates path using certain method (swaps etc. TODO: decide on a method)
    void generateNeighbourPath2();           // generates path using certain method (swaps etc. TODO: decide on a method)
    void epoch(int currentIteration, int maxIterations,  float, float);       // loop method, loop for set times and tries to calculate the most optimal res
    int calculatePathCost(int path[]);      // for a given path calculates it cost
    void printPath(int *path);              // printing given path, will be used in creating result
    void generateRandomPath();


    // fields

    Graph g;                    // graph object passed to the class TODO: mby it dont need to be stored, all important data is extracted anyway
    int numOfCities;            // size of the graph
    int *bestPath;              // stores the best already found path, should be initialized with all -1?
    int bestPathCost = INT_MAX;
    int *currentPath;           // stores currently calculated path
    int currentPathCost = INT_MAX;
    int *neighbourPath;         // stores next step path
    int neighbourPathCost = INT_MAX;
    int endCondition;           // specific end condition - prbly will specify number of the iteration - epochs
    int **matrix;               // extracted matrix from graph class to have more convenient access
    int iterations_since_last_change;
    MoveQueue tabulist;

    void shaking();

    void generateNeighbourPath2Opt();

    string getBestPath();
    int getBestPathValue();

    void grasp(float);
};


#endif //P1_TS_H
