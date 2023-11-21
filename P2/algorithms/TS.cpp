//
// Created by stani on 18.11.2023.
//

#include "TS.h"
#include "random"
using namespace std;

TS::TS(Graph graph) : tabulist(10){
    numOfCities = graph.getSize();
    g = graph;                              // may not be necessary
    matrix = g.getMatrix();
    bestPath = new int[numOfCities];
    neighbourPath = new int[numOfCities];
    currentPath = new int[numOfCities];

}


void TS::apply(int maxIterations){

    generateFirstPath();
//    bestPath = currentPath;
    srand(time(NULL));


    /// loop trying to calculate best solution
    for(int i = 0; i < maxIterations; i++){
        epoch(i);
    }

    cout<<"Best found cost: " << bestPathCost <<" vs "<<calculatePathCost(bestPath)<<"\n";
    cout<<"Path: ";
    printPath(bestPath);
}


void TS::epoch(int currentIteration) {
    // calculate new path
    generateNeighbourPath();
    neighbourPathCost = calculatePathCost(neighbourPath);
/*
    cout<<"Ite: " << currentIteration <<" neighbour path: ";
    for(int i =0; i <numOfCities; i++){
        cout<<neighbourPath[i] << ", ";
    }
    cout<<"Cost: "<< neighbourPathCost <<"\n\n\n";
*/


    if( neighbourPathCost < currentPathCost){
        // copies neighbourPath to currentPath
        std::copy(neighbourPath, neighbourPath + numOfCities, currentPath);
        currentPathCost = neighbourPathCost;

        // keeping track of the best ever found result
        if(currentPathCost < bestPathCost){
            // copies currentPath to bestPath
            std::copy(currentPath, currentPath + numOfCities, bestPath);
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

        if (random_number < 1.0 - 1.0 / currentIteration) {
            // copies neighbourPath to currentPath
            std::copy(neighbourPath, neighbourPath + numOfCities, currentPath);
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
    } while (pos1 == pos2 or tabulist.findMove(pos1, pos2));

    // Apply the move
    //memcpy(neighbourPath, currentPath, numOfCities * sizeof(int));
    for(int i = 0; i < numOfCities; i++){
        neighbourPath[i] = currentPath[i];
    }
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

    // Przechodzimy przez wszystkie wierzchołki ścieżki, z wyjątkiem pierwszego i ostatniego
    for (int i = 1; i < numOfCities - 1; i++) {
        cost += matrix[path[i - 1]][path[i]];
    }

    // Dodajemy koszt podróży z ostatniego wierzchołka do pierwszego
    cost += matrix[path[numOfCities - 1]][path[0]];

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
    std::copy(solution, solution + numOfCities, currentPath);

}

void TS::printPath(int *path) {
    for(int i = 0; i< numOfCities; i++){
        cout<<path[i]<<", ";
    }
    cout<<path[0]<<endl;
}


