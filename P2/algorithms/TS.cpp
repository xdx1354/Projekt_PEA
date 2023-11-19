//
// Created by stani on 18.11.2023.
//

#include "TS.h"
#include "random"
using namespace std;

TS::TS(Graph graph){
    numOfCities = graph.getSize();
    g = graph;                              // may not be necessary
    matrix = g.getMatrix();

}


void TS::apply(int maxIterations){

    generateFirstPath();
    bestPath = currentPath;

    // initializing the tabu list

    tabulist = new int*[numOfCities];
    for (int i = 0; i < numOfCities; ++i) {
        tabulist[i] = new int[numOfCities];
        for (int j = 0; j < numOfCities; ++j) {
            tabulist[i][j] = -1; // Ustawiamy na -1 jako początkową wartość
        }
    }

    bestPath = new int[numOfCities];
    neighbourPath = new int[numOfCities];
    currentPath = new int[numOfCities];

    /// should i fill them with initial data?


    /// loop trying to calculate best solution
    for(int i = 0; i < maxIterations; i++){
        epoch();
    }
}


void TS::epoch() {
    // calculate new path
    generateNeighbourPath();
    neighbourPathCost = calculatePathCost(neighbourPath);

    if( neighbourPathCost < currentPathCost){
        currentPath = neighbourPath;
        currentPathCost = neighbourPathCost;

        // keeping track of the best ever found result
        if(currentPathCost < bestPathCost){
            bestPath = currentPath;
            bestPathCost = currentPathCost;
        }


        //?? any other restrains should be added despite adding this path to tabu just after generating it???

    }
    else {
        // randomly chosen chance generated to pick neighbour solution even if it worse than currently held one
        // in purpose to leave the local minimum
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double random_number = dis(gen);

        if (random_number < 1.0 - 1.0 / tabulistLength) {
            currentPath = neighbourPath;
            currentPathCost = neighbourPathCost;
        }
    }
}

/**
 * generates neighbour path for path stored in currentPath
 * @return generated path as integer pointer
 */
void TS::generateNeighbourPath() {
    int pos1, pos2;
    do {
        pos1 = rand() % (numOfCities - 1) + 1;
        pos2 = rand() % (numOfCities - 1) + 1;
    } while (pos1 == pos2 || tabulist[pos1][pos2] != -1);

    // Apply the move
    memcpy(neighbourPath, currentPath, numOfCities * sizeof(int));
    swap(neighbourPath[pos1], neighbourPath[pos2]);
    neighbourPathCost = calculatePathCost(neighbourPath);
}

/**
 * Calculates cost of traveling current path. Includes last step to starting city.
 * TODO: should first city be always the same?
 * @param path: array of integers
 * @return
 */
int TS::calculatePathCost(int *path) {
    int cost = 0;
    for(int i = 1; i < numOfCities; i++){
        cost += matrix[path[i-1]][path[i]];
    }
    cost += matrix[path[numOfCities-1]][path[0]];               // adding cost of coming back to starting point

    return cost;
}

/**
 * First path will be generated randomly
 * @return
 */
void TS::generateFirstPath() {

    int* solution = new int[numOfCities];
    for (int i = 0; i < numOfCities; ++i) {
        solution[i] = i;
    }
    // Losowe przemieszanie miast, z pominięciem pierwszego (miasta startowego)
    for (int i = 1; i < numOfCities - 1; ++i) {
        int j = rand() % (numOfCities - i) + i;
        std::swap(solution[i], solution[j]);
    }
}

void TS::printPath(int *path) {
    for(int i = 0; i< numOfCities; i++){
        cout<<path[i]<<", ";
    }
    cout<<path[0]<<endl;

}

