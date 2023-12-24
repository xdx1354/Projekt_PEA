//
// Created by stani on 23.12.2023.
//

#include "Genetic.h"
#include "iostream"
#include <algorithm>
//#include <iterator>
//#include <random>


Genetic::Genetic(Graph graph, int numOfIterations, int sizeOfPopulation, int crossCount, int mutateCount)
        : bestPath(bestPath) {

    srand(time(NULL));

    g = graph;
    matrix = g.getMatrix();
    numOfCities = g.getSize();

    currentNumOfPaths = 0;
    pathsListSize = sizeOfPopulation + crossCount + mutateCount;
    populationSize = sizeOfPopulation;
    bestCost = INT_MAX;

    listOfPaths = new Path[pathsListSize];

    // initializing list with empty objects of path
    for(int i = 0; i < pathsListSize; i++){
        Path p(numOfCities);
        listOfPaths[i] = Path(numOfCities);
    }

    this -> crossCount = crossCount;
    this -> mutateCount = mutateCount;

    Path p(numOfCities);
    bestPath = p;
    p.setCost(INT_MAX);
}

void Genetic::apply(int numOfIterations) {


    // generate random paths x sizeOfPopulation
    for(int i = 0; i < populationSize; i++){
        listOfPaths[i] = generateRandomPath();

    }
    currentNumOfPaths = populationSize;

    std::cout<<"Rand paths generated\n";




    //main loop iterating through epochs
    for(int i = 0; i < numOfIterations; i++){
        epoch(i);
    }

    pickTopResults();
    printCurrentList();
    std::cout<<"Cheapest ever path cost: " <<bestCost<<"\n";
    std::cout<<"Cheapest path cost: " <<listOfPaths[0].getCost()<<"\n";
    std::cout<<"2nd cheapest path cost: " <<listOfPaths[1].getCost()<<"\n";
}

void Genetic::epoch(int currentIteration) {

    for(int i = 0; i < crossCount; i++){

        int first, second;
        do{
            first = rand() % populationSize;
            second = rand() % populationSize;
        } while (first == second);

        listOfPaths[currentNumOfPaths] = cross(listOfPaths[first], listOfPaths[second]);
        currentNumOfPaths++;
    }


    for(int i = 0; i < mutateCount; i++){

        listOfPaths[currentNumOfPaths] = mutate(listOfPaths[rand() % populationSize]);
        currentNumOfPaths++;

    }

    std::cout<<"Epoch: " + std::to_string(currentIteration) <<"\n";
//    printCurrentList();
    std::cout<<"\n\n";

    pickTopResults();

}

void Genetic::pickTopResults() {
    int bestCurrentCost = INT_MAX;

    // calculate current costs TODO: this should be done while adding a new path to save time

    /// THIS IS JUST A HOTFIX
    for(int i = 0; i < numOfCities; i++){
        listOfPaths[i].calculateCost(g);
    }


    // bubble sort
    for (int i = 0; i < populationSize - 1; i++) {
        for (int j = 0; j < populationSize - i - 1; j++) {
            if (listOfPaths[j].getCost() > listOfPaths[j + 1].getCost()) {
                std::swap(listOfPaths[j], listOfPaths[j + 1]);
            }
        }
    }

    // check if new best result found
    bestCurrentCost = listOfPaths[0].getCost();
    if (bestCurrentCost < bestCost) {
        bestCost = bestCurrentCost;
    }

    // ignore paths at the end
    currentNumOfPaths = populationSize;
}


Path Genetic::cross(Path A, Path B) {
    int *newPath = new int[numOfCities];
    Path newObjPath(numOfCities);

    // Take the first half of cities from Path A
    for (int i = 0; i < numOfCities / 2; i++) {
        newPath[i] = A.getCitiesList()[i];
    }

    // Fill the remaining cities from Path B
    int counter = numOfCities / 2;
    for (int i = 0; i < numOfCities; i++) {
        int potentialCity = B.getCitiesList()[i];
        bool isPresent = false;

        // Check if the city is already present in the first half of newPath
        for (int j = 0; j < numOfCities / 2; j++) {
            if (potentialCity == newPath[j]) {
                isPresent = true;
                break;
            }
        }

        // If the city is not present, add it to newPath
        if (!isPresent) {
            newPath[counter] = potentialCity;
            counter++;
        }

        // Check if all cities are added to newPath
        if (counter >= numOfCities) {
            break;
        }
    }

    newObjPath.setCitiesList(newPath);
//    std::cout<<"\n Path: "<<newObjPath.to_string();
    newObjPath.calculateCost(g);
//    std::cout<<"  worked well\n";

    delete[] newPath; // Free dynamically allocated memory

    return newObjPath;
}

Path Genetic::mutate(Path A) {

    int *newPath = new int[numOfCities];
    Path newObjPath(numOfCities);

    newPath = A.getCitiesList();


    int first, second;
    do{
        first = rand() % numOfCities;
        second = rand() % numOfCities;
    } while (first == second);

    std::swap(newPath[first], newPath[second]);

    newObjPath.setCitiesList(newPath);
    newObjPath.calculateCost(g);

    return  newObjPath;
}


Path Genetic::generateRandomPath() {
    Path p(numOfCities);

    // Initialize the cities list in Path p
    int* cities = new int[numOfCities];
    for (int i = 0; i < numOfCities; ++i) {
        cities[i] = i;
    }
    p.setCitiesList(cities);

    // Shuffle the cities list
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cities, cities + numOfCities, gen);

    p.calculateCost(g);

    return p;
}

void Genetic::printCurrentList() {
    for( int i = 0; i < currentNumOfPaths; i++){
        listOfPaths[i].calculateCost(g);
        std::cout<<listOfPaths[i].to_string() <<"    COST: " << listOfPaths[i].getCost();
//        std::cout<<listOfPaths[i].getCitiesList()[0]<<currentNumOfPaths;

        std::cout<<"\n";
    }
}


/// GETTERS SETTERS
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

Genetic::~Genetic() {

}
