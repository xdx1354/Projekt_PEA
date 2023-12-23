//
// Created by stani on 23.12.2023.
//

#include "Genetic.h"
#include "iostream"



Genetic::Genetic(int numOfIterations, int sizeOfPopulation, int crossCount, int mutateCount, Path bestPath)
        : bestPath(bestPath) {

    srand(time(NULL));

    currentNumOfPaths = 0;
    pathsListSize = sizeOfPopulation + crossCount + mutateCount;
    populationSize = sizeOfPopulation;
    bestCost = INT_MAX;

    // initializing list with empty objects of path
    for(int i = 0; i < pathsListSize; i++){
        Path p(numOfCities);
        listOfPaths[i] = p;
    }

    this -> crossCount = crossCount;
    this -> mutateCount = mutateCount;

    Path p(numOfCities);
    bestPath = p;
    p.setCost(INT_MAX);
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

    pickTopResults();

}

void Genetic::pickTopResults() {
    int bestCurrentCost = INT_MAX;

    //bubble sort
    for(int i = 0; i < populationSize - 1; i++){
        for(int j = i+1; j < populationSize; j++){
            if(listOfPaths[j].getCost() > listOfPaths[j+1].getCost()){
                std::swap(listOfPaths[j], listOfPaths[j+1]);
            }
        }
    }

    // check if new best result found
    bestCurrentCost = listOfPaths[0].getCost();
    if(bestCurrentCost < bestCost){
        bestCost = bestCurrentCost;
    }

    // ignore paths at the end
    currentNumOfPaths = populationSize;

}


int Genetic::getCurrentNumOfPaths() const {
    return currentNumOfPaths;
}

Path *Genetic::getListOfPaths() const {
    return listOfPaths;
}

int Genetic::getBestCost() const {
    return bestCost;
}

void Genetic::setCurrentNumOfPaths(int currentNumOfPaths) {
    Genetic::currentNumOfPaths = currentNumOfPaths;
}

void Genetic::setListOfPaths(Path *listOfPaths) {
    Genetic::listOfPaths = listOfPaths;
}

void Genetic::setBestCost(int bestCost) {
    Genetic::bestCost = bestCost;
}

const Path &Genetic::getBestPath() const {
    return bestPath;
}

void Genetic::setBestPath(const Path &bestPath) {
    Genetic::bestPath = bestPath;
}

int Genetic::getNumOfCities() const {
    return numOfCities;
}

void Genetic::setNumOfCities(int numOfCities) {
    Genetic::numOfCities = numOfCities;
}
