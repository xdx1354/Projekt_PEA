//
// Created by stani on 23.12.2023.
//

#ifndef P2_GENETIC_H
#define P2_GENETIC_H


#include "../data_structures/Path.h"
#include "../data_structures/Graph.h"

class Genetic {


public:
    void apply();                                       // function for applying the algorithm

    Path getBestPath() const;
    void setBestPath(const Path &bestPath);

    int getCurrentNumOfPaths() const;
    void setCurrentNumOfPaths(int currentNumOfPaths);

    void setListOfPaths(Path *listOfPaths);
    Path *getListOfPaths() const;

    void setBestCost(int bestCost);
    int getBestCost() const;

    void printBestPath();

    int getNumOfCities() const;

    void setNumOfCities(int numOfCities);

    /// constructor/destructor
    Genetic(Graph graph,int numOfIterations, int sizeOfPopulation, int crossCount, int mutateCount, int cross2Count, int mutate2Count);
    ~Genetic();

protected: Graph g{};

private:
    int currentNumOfPaths;          // number of currently stored paths in listOfPaths
    Path *listOfPaths;              // [X][10] - X must fit whole population and additional path developed in current epoch
                                    // therefore it has to be calculated in constructor
    Path bestPath;                  // best found path
    int bestCost;                   // best known cost

    int populationSize;             // number of paths at the beginning of each epoch
    int pathsListSize;              // fixed size of table storing all paths - X

    int crossCount;                 // number of cross operations
    int mutateCount;                // number of swaps
    int cross2Count;                // number of PMX operations
    int mutate2Count;               // number of inverts

    int numOfCities;                // number of cities
    int **matrix;                   // graph matrix
    int numOfIterations;            // number of epochs



private:

    /// method responsible for main logic of algo
    void epoch(int currentIteration);

    /// genetic operations
    std::tuple<Path, Path> cross(Path A, Path B);       // takes half of A and fills with B
    std::tuple<Path, Path> cross2(Path A, Path B);      // takes part of A and maps the rest of B  (PMX)

    /// mutate operations
    Path mutate(Path A);                                // swaps two random cities
    Path mutate2(Path A);                               // inverts path between two random cities


    ///utility methods
    void pickTopResults();              // it will sort and then save only top 10 results
    Path generateRandomPath();          // might be changed later to improve algo
    void printCurrentList();            // printing current population list


    Path generateGreedyPath();          // generating Greedy path
};


#endif //P2_GENETIC_H
