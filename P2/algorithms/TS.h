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

    /// MAIN LOGIC OF ALGORITHM METHODS
    void apply(int endCondition, float, float);          // running the algorithm, preparing var and objects
    void epoch(int currentIteration, int maxIterations,  float, float);       // loop method, loop for set times and tries to calculate the most optimal res

    /// PATH GENERATIONS METHODS
    void generateNeighbourPath();           // generates neighbour solution by swapping two cities
    void shaking();                         // shuffles random subset (part of the path) in order to escape local minimum
    void generateNeighbourPath2Opt();       // generates neighbour solution by swapping direction of subset between two cities
    void grasp(float);                      // generates initial solution, in fact acts as greedy algo for chosen alpha

    /// UTILITY METHODS
    int calculatePathCost(int path[]);      // for a given path calculates it cost
    void printPath(int *path);              // printing given path
    void printResult();                     // printing result

    /// unused methods - some because were inefficient, other because the conception changed
    /// they are working and can be useful in futer for further developments
    void generateFirstPath();               // generates initial path with greedy algo
    void generateNeighbourPath2();          // generates neighbour solution by swapping two pairs of cities
    void generateRandomPath();              // randomly generates new path - it was less efficient than grasp
    string getBestPath();                   // for returning just best path
    int getBestPathValue();                 // for returning best path value

    // fields

    Graph g;                            // graph object passed to the class
    int numOfCities;                    // size of the graph
    int *bestPath;                      // stores the best already found path, should be initialized with all -1?
    int bestPathCost = INT_MAX;
    int *currentPath;                   // stores currently calculated path
    int currentPathCost = INT_MAX;
    int *neighbourPath;                 // stores next step path
    int neighbourPathCost = INT_MAX;
    int endCondition;                   // specific end condition - probably will specify number of the iteration - epochs
    int **matrix;                       // extracted matrix from graph class to have more convenient access
    int iterations_since_last_change;   // used for keeping track of progress of alg, helpful to detect local optimum areas
                                        // where algorithm can easily get stuck
    MoveQueue tabulist;                 // tabu list object represented by cyclic queue


};


#endif //P1_TS_H
