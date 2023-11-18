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

    currentPath = generateFirstPath();
    bestPath = currentPath;

    // initializing the tabu list
    tabulist = new int*[maxIterations];
    for (int i = 0; i < maxIterations; ++i) {
        tabulist[i] = new int[numOfCities];
    }

    //TODO: initialize the bestPath, neighbourPath, currentPath

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
    // should add the generated result to tabu list
    int pos1 = rand() % (numOfCities - 1) + 1;
    int pos2 = rand() % (numOfCities - 1) + 1;

    // assert that pos1 and pos2 are not the same
    // excludes possibility of empty iteration when getting no change in path
    while (pos1 == pos2){
        pos2 = rand() % (numOfCities - 1) + 1;
    }
//    int* neighbor_solution = new int[numOfCities];
    memcpy(neighbourPath, currentPath, numOfCities * sizeof(int));      // copying the data to new array
    swap(neighbourPath[pos1], neighbourPath[pos2]);                     // swapping two cities
    neighbourPathCost = calculatePathCost(neighbourPath);               // updating the cost

    ///TODO: check tabu, if its already in tabu list -> generate again and so on
}

