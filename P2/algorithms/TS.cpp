//
// Created by stani on 18.11.2023.
//

#include "TS.h"
using namespace std;

TS::TS(Graph graph){
    numOfCities = graph.getSize();
    g = graph;                              // may not be necessary
    matrix = g.getMatrix();

}


void TS::apply(int maxIterations){
    // setting initial result
    currentPath = generateFirstPath();
    bestPath = currentPath;

    /// loop trying to calculate best solution
    for(int i = 0; i < maxIterations; i++){
        epoch();
    }
}


void TS::epoch() {
    // calcualate new path
    currentPath = generateNextPath();
    if(calculatePathCost(currentPath) < bestPathCost){

    }
}

