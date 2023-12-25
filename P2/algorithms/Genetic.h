//
// Created by stani on 23.12.2023.
//

#ifndef P2_GENETIC_H
#define P2_GENETIC_H


#include "../data_structures/Path.h"
#include "../data_structures/Graph.h"

class Genetic {


public:
    void apply();

    const Path &getBestPath() const;
    void setBestPath(const Path &bestPath);

    int getCurrentNumOfPaths() const;
    void setCurrentNumOfPaths(int currentNumOfPaths);

    void setListOfPaths(Path *listOfPaths);
    Path *getListOfPaths() const;

    void setBestCost(int bestCost);
    int getBestCost() const;

private:
    int currentNumOfPaths;          // number of currently stored paths in listOfPaths
    Path *listOfPaths;              // [X][10] - X must fit whole population and additional path developed in current epoch
                                    // therefore it has to be calculated in constructor
    Path bestPath;
    int bestCost;

    int populationSize;             // number of paths at the beginning of each epoch
    int pathsListSize;              // X

    int crossCount;
    int mutateCount;

    int numOfCities;
    Graph g;
    int **matrix;
    int numOfIterations;


public:
    int getNumOfCities() const;

    void setNumOfCities(int numOfCities);

    /// constructor/destructor
    Genetic(Graph graph,int numOfIterations, int sizeOfPopulation, int crossCount, int mutateCount);
    ~Genetic();

private:




    /// method responsible for main logic of algo
    void epoch(int currentIteration);

    /// genetic operations
    std::tuple<Path, Path> cross(Path A, Path B);       // takes half of A and fills with B
    Path mutate(Path A);             // swaps two cities


    ///utility methods
    void pickTopResults();           // it will sort and then save only top 10 results
    Path generateRandomPath();      // might be changed later to improve algo
    void printCurrentList();


    std::tuple<Path, Path> cross2(Path A, Path B);

    Path mutate2(Path A);
};


#endif //P2_GENETIC_H
