//
// Created by stani on 23.12.2023.
//

#ifndef P2_GENETIC_H
#define P2_GENETIC_H


#include "../data_structures/Path.h"

class Genetic {


public:
    void apply(int numOfIterations);

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
public:
    int getNumOfCities() const;

    void setNumOfCities(int numOfCities);

private:


    /// constructor/destructor
    Genetic(int numOfIterations, int sizeOfPopulation, int probabilityOfCross, int probabilityOfMutation,
            Path bestPath);
    ~Genetic();

    /// method responsible for main logic of algo
    void epoch(int currentIteration);

    /// genetic operations
    int* cross(int A, int B);       // takes half of A and fills with B
    int* mutate(int A);             // swaps two cities


    ///utility methods
    void pickTopResults();           // it will sort and then save only top 10 results
    Path generateRandomPath();      // might be changed later to improve algo


};


#endif //P2_GENETIC_H
