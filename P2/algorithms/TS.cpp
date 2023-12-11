//
// Created by stani on 18.11.2023.
//

#include "TS.h"
#include "random"
using namespace std;

TS::TS(Graph graph) : tabulist(20){
    numOfCities = graph.getSize();
    g = graph;                              // may not be necessary
    matrix = g.getMatrix();
    bestPath = new int[numOfCities];
    neighbourPath = new int[numOfCities];
    currentPath = new int[numOfCities];
    iterations_since_last_change = 0;

}


void TS::apply(int maxIterations, float q1, float q2){

    srand(time(NULL));

//    generateFirstPath();
//    bestPath = currentPath;
    grasp(1);

    /// loop trying to calculate best solution
    for(int i = 0; i < maxIterations; i++){
        epoch(i, maxIterations, q1, q2);

    }

    printPath(bestPath);
//    cout<<"\nBest cost: "<<bestPathCost;

}


void TS::epoch(int currentIteration, int maxIterations, float q1, float q2) {
    // calculate new path
    bool _shaking = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double random_number = dis(gen);

    if(iterations_since_last_change >= maxIterations * 0.1){
        tabulist.clear();
        shaking();
        _shaking = 1;
    }
    else{
        if (random_number < q1) {
            generateNeighbourPath(); // Probability of q1 to use generateNeighbourPath()
        }else{
            generateNeighbourPath2Opt(); // Probability of q3 to use generateNeighbourPath2Opt()
        }
    }





//    cout<<"Ite: " << currentIteration <<" neighbour path: ";
//    for(int i =0; i <numOfCities; i++){
//        cout<<neighbourPath[i] << ", ";
//    }
//    cout<<"Cost: "<< neighbourPathCost <<"\n\n\n";



    if( neighbourPathCost < currentPathCost or _shaking){

        iterations_since_last_change = 0;

        // copies neighbourPath to currentPath
        std::copy(neighbourPath, neighbourPath + numOfCities, currentPath);
        currentPathCost = calculatePathCost(currentPath);

        // keeping track of the best ever found result
        if(currentPathCost < bestPathCost){
            // copies currentPath to bestPath
            std::copy(currentPath, currentPath + numOfCities, bestPath);
            bestPathCost = calculatePathCost(bestPath);
        }


    }
    else{
    iterations_since_last_change++;
    }

}

/**
 * generates neighbour path for path stored in currentPath
 * @return generated path as integer pointer
 */
void TS::generateNeighbourPath() {
    int pos1, pos2;

    std::copy(currentPath, currentPath + numOfCities, neighbourPath);

    do {
        pos1 = rand() % (numOfCities - 1) + 1;
        pos2 = rand() % (numOfCities - 1) + 1;
    } while (pos1 == pos2 or tabulist.findMove(pos1, pos2));

    // Apply the move
    // memcpy(neighbourPath, currentPath, numOfCities * sizeof(int));
    tabulist.push(pos1, pos2);
    for(int i = 0; i < numOfCities; i++){
        neighbourPath[i] = currentPath[i];
    }
    swap(neighbourPath[pos1], neighbourPath[pos2]);
    neighbourPathCost = calculatePathCost(neighbourPath);
}

void TS::generateNeighbourPath2() {

    int pos1, pos2, pos3, pos4;

    std::copy(currentPath, currentPath + numOfCities, neighbourPath);

    do {
        pos1 = rand() % (numOfCities / 2 - 1) + 1;
        pos2 = rand() % (numOfCities / 2 - 1) + 1;
        pos3 = rand() % (numOfCities - 1) + 1;
        pos4 = rand() % (numOfCities - 1) + 1;
    }while(pos1 != pos2 or pos3 != pos4 or tabulist.findMove(pos1, pos2) or tabulist.findMove(pos3, pos4));

    swap(neighbourPath[pos1], neighbourPath[pos2]);
    swap(neighbourPath[pos3], neighbourPath[pos4]);
    neighbourPathCost = calculatePathCost(neighbourPath);
    tabulist.push(pos1, pos2);
    tabulist.push(pos3, pos4);


}

void TS::generateNeighbourPath2Opt() {
    std::copy(currentPath, currentPath + numOfCities, neighbourPath);

    int pos1, pos2;
    do {
        pos1 = rand() % (numOfCities - 1) + 1;
        pos2 = rand() % (numOfCities - 1) + 1;
    } while (pos1 == pos2 || abs(pos1 - pos2) < 2 || tabulist.findMove(pos1, pos2));

    tabulist.push(pos1, pos2);


    if (pos1 > pos2) {
        std::swap(pos1, pos2);
    }

    // Apply 2-opt swap
    while (pos1 < pos2) {
        std::swap(neighbourPath[pos1], neighbourPath[pos2]);
        pos1++;
        pos2--;
    }

    neighbourPathCost = calculatePathCost(neighbourPath);

}

void TS::shaking() {
    std::copy(currentPath, currentPath + numOfCities, neighbourPath);

    // Perform a big jump by shuffling a subset of cities (e.g., shuffle cities between pos1 and pos2)
    int pos1 = rand() % (numOfCities - 1) + 1;
    int pos2 = rand() % (numOfCities - 1) + 1;

    if (pos1 > pos2) {
        std::swap(pos1, pos2);
    }

    int subsetSize = pos2 - pos1 + 1;
    int* tempSubset = new int[subsetSize];

    // Copy the subset of cities to tempSubset
    std::copy(neighbourPath + pos1, neighbourPath + pos2 + 1, tempSubset);

    // Shuffle the subset of cities using Fisher-Yates shuffle algorithm
    for (int i = subsetSize - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(tempSubset[i], tempSubset[j]);
    }

    // Copy the shuffled subset back to neighbourPath
    std::copy(tempSubset, tempSubset + subsetSize, neighbourPath + pos1);

    neighbourPathCost = calculatePathCost(neighbourPath);

    // Clean up memory
    delete[] tempSubset;
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
    for (int i = 1; i < numOfCities; i++) {
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
    bool* visited = new bool[numOfCities] {false}; // Keep track of visited cities
    solution[0] = rand() % numOfCities; // Start from a random city
    visited[solution[0]] = true;

    for (int i = 1; i < numOfCities; ++i) {
        int currentCity = solution[i - 1];
        int nearestCity = -1;
        int minDistance = INT_MAX;

        for (int j = 0; j < numOfCities; ++j) {
            if (!visited[j] && matrix[currentCity][j] < minDistance) {
                minDistance = matrix[currentCity][j];
                nearestCity = j;
            }
        }

        solution[i] = nearestCity;
        visited[nearestCity] = true;
    }

    std::copy(solution, solution + numOfCities, currentPath);
    std::copy(solution, solution + numOfCities, bestPath);
    bestPathCost = calculatePathCost(solution);
    currentPathCost = calculatePathCost(currentPath);

    delete[] solution;
    delete[] visited;
}
//TODO: opracować, dodać dokumetacje
void TS::grasp(float alpha) {
    int* solution = new int[numOfCities];
    bool* visited = new bool[numOfCities] {false}; // Keep track of visited cities
    solution[0] = rand() % numOfCities; // Start from a random city
    visited[solution[0]] = true;

    for (int i = 1; i < numOfCities; ++i) {
        int currentCity = solution[i - 1];
        int nearestCity = -1;
        int minDistance = INT_MAX;
        int* candidates = new int[numOfCities]; // Candidates list to store cities close enough to endpoints
        int numCandidates = 0;

        for (int j = 0; j < numOfCities; ++j) {
            if (!visited[j] && matrix[currentCity][j] < minDistance) {
                minDistance = matrix[currentCity][j];
            }
        }

        // Populate candidates list with cities close enough to endpoints
        for (int j = 0; j < numOfCities; ++j) {
            if (!visited[j] && matrix[currentCity][j] <= minDistance * alpha) {
                candidates[numCandidates++] = j;
            }
        }

        // Randomly select a city from candidates list
        if (numCandidates > 0) {
            int randomIndex = rand() % numCandidates;
            nearestCity = candidates[randomIndex];
        } else {
            // If no candidates found, choose a random unvisited city
            do {
                nearestCity = rand() % numOfCities;
            } while (visited[nearestCity]);
        }

        solution[i] = nearestCity;
        visited[nearestCity] = true;
        delete[] candidates;
    }

    std::copy(solution, solution + numOfCities, currentPath);
    std::copy(solution, solution + numOfCities, bestPath);
    bestPathCost = calculatePathCost(solution);
    currentPathCost = calculatePathCost(currentPath);

    delete[] solution;
    delete[] visited;

//    printPath(currentPath);
}




void TS::printPath(int *path) {
    for(int i = 0; i< numOfCities; i++){
        cout<<path[i]<<", ";
    }
    cout<<path[0]<<endl;
}

void TS::generateRandomPath() {
    for(int i = 0; i < 20; i++){
        int pos1 = rand()%(numOfCities-1);
        int pos2 = rand()%(numOfCities-1);
        swap(currentPath[pos1], currentPath[pos2]);
        currentPathCost = calculatePathCost(currentPath);
    }



}


string TS::getBestPath() {

    string message;
    for( int i = 0; i < numOfCities; i++){
//        message +=
    }  
}


