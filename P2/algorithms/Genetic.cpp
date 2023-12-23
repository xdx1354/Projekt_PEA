//
// Created by stani on 23.12.2023.
//

#include "Genetic.h"
#include "iostream"



Genetic::Genetic(int numOfIterations,  int sizeOfPopulation, int crossCount, int mutateCount) {

    srand(time(NULL));

    currentNumOfPaths = 0;
    pathsListSize = sizeOfPopulation + crossCount + mutateCount;
    populationSize = sizeOfPopulation;
    bestCost = INT_MAX;
    bestPathFound = nullptr;

    // initializing list as empty
    for(int i = 0; i < pathsListSize; i++){
        listOfPaths[i] = nullptr;
    }

    this -> crossCount = crossCount;
    this -> mutateCount = mutateCount;
}

void Genetic::apply(int numOfIterations) {

    //fill with initial values

    // generate random paths x sizeOfPopulation
    for(int i = 0; i < populationSize; i++){
        listOfPaths[i] = generateRandomPath();
    }


    //main loop iterating through epochs
    for(int i = 0; i < numOfIterations; i++){
        epoch(i);
    }
}

void Genetic::epoch(int currentIteration) {

    for(int i = 0; i < crossCount; i++){
        cross(rand() % populationSize, rand() % populationSize);
    }


    for(int i = 0; i < mutateCount; i++){
        mutate(rand() % populationSize);
    }

    picTopResults();

}

void Genetic::picTopResults() {




}


int Genetic::getCurrentNumOfPaths() const {
    return currentNumOfPaths;
}

int **Genetic::getListOfPaths() const {
    return listOfPaths;
}

int *Genetic::getBestPathFound() const {
    return bestPathFound;
}

int Genetic::getBestCost() const {
    return bestCost;
}

void Genetic::setCurrentNumOfPaths(int currentNumOfPaths) {
    Genetic::currentNumOfPaths = currentNumOfPaths;
}

void Genetic::setListOfPaths(int **listOfPaths) {
    Genetic::listOfPaths = listOfPaths;
}

void Genetic::setBestPathFound(int *bestPathFound) {
    Genetic::bestPathFound = bestPathFound;
}

void Genetic::setBestCost(int bestCost) {
    Genetic::bestCost = bestCost;
}
