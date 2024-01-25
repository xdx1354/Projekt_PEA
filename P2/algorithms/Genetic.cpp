//
// Created by stani on 23.12.2023.
//

#include "Genetic.h"
#include "iostream"
#include <algorithm>


/**
 *
 * @param graph - Graph class object containing graph data
 * @param numOfIterations - limit of epochs
 * @param sizeOfPopulation  - limit of size of population selected after epoch for further development
 * @param crossCount - number of cross operations per epoch
 * @param mutateCount - number of mutate operations per epoch
 * @param cross2Count - number of cross (2nd method) operations per epoch
 * @param mutate2Count - number of mutate (2nd method) operations per epoch
 */
Genetic::Genetic(Graph graph, int numOfIterations, int sizeOfPopulation, int crossCount, int mutateCount, int cross2Count, int mutate2Count)
{

    srand(time(NULL));

    g = graph;
    matrix = g.getMatrix();
    numOfCities = g.getSize();

    currentNumOfPaths = 0;
    pathsListSize = sizeOfPopulation + 2 * crossCount + 2 * cross2Count + mutateCount + mutate2Count;
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
    this -> cross2Count = cross2Count;
    this -> mutate2Count = mutate2Count;
    this -> numOfIterations = numOfIterations;

    Path p(numOfCities);
    bestPath = p;
    p.setCost(INT_MAX);
}

void Genetic::apply() {


    // generate random paths x sizeOfPopulation

    listOfPaths[0] = generateGreedyPath();
    listOfPaths[0].calculateCost(g);

    for(int i = 1; i < populationSize; i++){
        listOfPaths[i] = generateRandomPath();
        listOfPaths[i].calculateCost(g);

    }
    currentNumOfPaths = populationSize;


    //main loop iterating through epochs
    for(int i = 0; i < numOfIterations; i++){
        epoch(i);
    }

    pickTopResults();

    std::cout<<"Cheapest ever path cost: " <<bestCost<<"\n";

}

void Genetic::epoch(int currentIteration) {

    //// for some reason performing twice operation on same paths causes segfault because number of the nodes are inncorrect
    //// for example 600 instead of in range of (0, 10). Somehow first action affects the data/

/// Performing crossCount crossing operations


    /// CROSS action
    for(int i = 0; i < crossCount; i++){

        int first, second;
        do{
            first = rand() % (populationSize/2);
            second = rand() % (populationSize);
        } while (first == second);


        //std::cout<<"First path: " << listOfPaths[first].to_string() <<" \n";
        //std::cout<<"Second path: " << listOfPaths[second].to_string() <<" \n\n";
        std::tuple<Path, Path> crossResult = cross(listOfPaths[first], listOfPaths[second]);

        listOfPaths[currentNumOfPaths] = std::get<0>(crossResult);
        //std::cout<<"First child: " << listOfPaths[currentNumOfPaths].to_string() <<" \n\n";
        currentNumOfPaths++;

        listOfPaths[currentNumOfPaths] = std::get<1>(crossResult);
        //std::cout<<"Second child: " << listOfPaths[currentNumOfPaths].to_string() <<" \n\n";
        currentNumOfPaths++;

        //std::cout<<"--------------------\n";

    }


    /// CROSS 2 action
    for(int i = 0; i < cross2Count; i++){

        int first, second;
        do {
            first = rand() % (populationSize / 2);
            second = rand() % (populationSize);
        } while (first == second);

        std::tuple<Path, Path> crossResult2 = cross2(listOfPaths[first], listOfPaths[second]);
        listOfPaths[currentNumOfPaths] = std::get<0>(crossResult2);
        currentNumOfPaths++;
        listOfPaths[currentNumOfPaths] = std::get<1>(crossResult2);
        currentNumOfPaths++;

    }



    /// MUTATE ACTION
    for(int i = 0; i < mutateCount; i++){

        listOfPaths[currentNumOfPaths] = mutate(listOfPaths[rand() % populationSize]);
        currentNumOfPaths++;

    }


    /// MUTATE 2 ACTION
    for(int i = 0; i < mutate2Count; i++){

        listOfPaths[currentNumOfPaths] = mutate2(listOfPaths[rand() % (populationSize)]);
        currentNumOfPaths++;

    }


//    std::cout<<"Epoch: " + std::to_string(currentIteration) <<"\n";
//    printCurrentList();
//    std::cout<<"\n\n";



/// Calling pickTopResults function to sort all results and store only the top X one, where X = sizeOfPopulation
    pickTopResults();
//    printCurrentList();

//    std::cout<<"\n-----------------\n";

}

void Genetic::pickTopResults() {
    int bestCurrentCost = INT_MAX;


    for(int i = 0; i < currentNumOfPaths; i++){
        listOfPaths[i].calculateCost(g);
    }


    std::sort(listOfPaths, listOfPaths + currentNumOfPaths, [](const Path& a, const Path& b) {
        return a.getCost() < b.getCost(); // Sort in ascending order of cost
    });


    // check if new best result found
    bestCurrentCost = listOfPaths[0].getCost();
    if (bestCurrentCost < bestCost) {
        bestCost = bestCurrentCost;
        bestPath.setCitiesList(listOfPaths[0].getCitiesList());
        bestPath.calculateCost(g);
    }

    for(int i = populationSize; i < currentNumOfPaths; i++) {
        delete[] listOfPaths[i].getCitiesList();
    }

    // ignore paths at the end
    currentNumOfPaths = populationSize;
}


/**
 * Takes half of path A and fill with lacking nodes in order of appearing in B.
 * @param A first parent path
 * @param B second parent path
 * @return Tuple of two paths
 */
std::tuple<Path, Path> Genetic::cross(Path A, Path B) {
    int* newPathA = new int[numOfCities];
    int* newPathB = new int[numOfCities];

    Path newObjPathA(numOfCities);
    Path newObjPathB(numOfCities);

    // Generating the first child path (newObjPathA)
    int counterA = 0;
    int pivot = rand() % numOfCities;

    // Take the first half of cities from Path A
    for (int i = 0; i < pivot; i++) {
        newPathA[i] = A.getCitiesList()[i];
        counterA++;
    }



    // Fill the remaining cities from Path B to form newObjPathA
    for (int i = 0; i < numOfCities; i++) {
        int potentialCity = B.getCitiesList()[i];
        bool isPresent = false;

        // Check if the city is already present in the first part of newPathA
        for (int j = 0; j < pivot; j++) {
            if (potentialCity == newPathA[j]) {
                isPresent = true;
                break;
            }
        }

        // If the city is not present, add it to newPathA
        if (!isPresent) {
            newPathA[counterA] = potentialCity;
            counterA++;
        }

        // Check if all cities are added to newPathA
        if (counterA >= numOfCities) {
            break;
        }
    }

    newObjPathA.setCitiesList(newPathA);
    newObjPathA.calculateCost(g);

    // Generating the second child path (newObjPathB)
    int counterB = 0;
    pivot = rand() % numOfCities;

    // Take the first half of cities from Path B
    for (int i = 0; i < pivot; i++) {
        newPathB[i] = B.getCitiesList()[i];
        counterB++;
    }

    // Fill the remaining cities from Path A to form newObjPathB
    for (int i = 0; i < numOfCities; i++) {
        int potentialCity = A.getCitiesList()[i];
        bool isPresent = false;

        // Check if the city is already present in the first half of newPathB
        for (int j = 0; j < pivot; j++) {
            if (potentialCity == newPathB[j]) {
                isPresent = true;
                break;
            }
        }

        // If the city is not present, add it to newPathB
        if (!isPresent) {
            newPathB[counterB] = potentialCity;
            counterB++;
        }

        // Check if all cities are added to newPathB
        if (counterB >= numOfCities) {
            break;
        }
    }

    newObjPathB.setCitiesList(newPathB);
    newObjPathB.calculateCost(g);

    delete[] newPathA; // Free dynamically allocated memory for newPathA
    delete[] newPathB; // Free dynamically allocated memory for newPathB

    return std::make_tuple(newObjPathA, newObjPathB);
}


/**

 * @param A Path - first parent
 * @param B Path - second parent
 * @return Tuple of two objects Path
 */
 std::tuple<Path, Path> Genetic::cross2(Path A, Path B) {
     int crossoverPoint = rand() % A.getSize();

     int *newA = new int[numOfCities];
     int *newB = new int[numOfCities];

     std::copy(A.getCitiesList(), A.getCitiesList() + A.getSize(), newA);
     std::copy(B.getCitiesList(), B.getCitiesList() + B.getSize(), newB);

     int *newAA = new int[numOfCities];
     int *newBB = new int[numOfCities];

     std::copy(A.getCitiesList(), A.getCitiesList() + A.getSize(), newAA);
     std::copy(B.getCitiesList(), B.getCitiesList() + B.getSize(), newBB);

     // First child path (p1)
     for (int i = 0; i < crossoverPoint; ++i) {
         int itemToInsert = newB[i];
         int itemToSwap = newA[i];

         if (itemToInsert != itemToSwap) {
             int index = -1;
             for (int j = 0; j < A.getSize(); ++j) {
                 if (newA[j] == itemToInsert) {
                     index = j;
                     break;
                 }
             }

             if (index != -1) {
                 std::swap(newA[i], newA[index]);
             }
         }
     }

     Path p1(A.getSize());
     p1.setCitiesList(newA);
     p1.calculateCost(g);

     // Second child path (p2)
     for (int i = 0; i < crossoverPoint; ++i) {
         int itemToInsert = newAA[i];
         int itemToSwap = newBB[i];

         if (itemToInsert != itemToSwap) {
             int index = -1;
             for (int j = 0; j < B.getSize(); ++j) {
                 if (newBB[j] == itemToInsert) {
                     index = j;
                     break;
                 }
             }

             if (index != -1) {
                 std::swap(newBB[i], newBB[index]);
             }
         }
     }

     Path p2(B.getSize());
     p2.setCitiesList(newBB);
     p2.calculateCost(g);

     delete[] newA;
     delete[] newB;

     delete[] newAA;
     delete[] newBB;

     return std::make_tuple(p1, p2);
 }


Path Genetic::mutate(Path A) {

    int *newPath = new int[numOfCities];
    Path newObjPath(numOfCities);

    std::copy(A.getCitiesList(), A.getCitiesList() + A.getSize(), newPath);


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

Path Genetic::mutate2(Path A){

    Path p(numOfCities);
    int *newPath = new int[numOfCities];

    std::copy(A.getCitiesList(), A.getCitiesList() + A.getSize(), newPath);


    int pos1, pos2;
    do {
        pos1 = rand() % (numOfCities - 1) + 1;
        pos2 = rand() % (numOfCities - 1) + 1;
    } while (pos1 == pos2 || abs(pos1 - pos2) < 2);




    if (pos1 > pos2) {
        std::swap(pos1, pos2);
    }

    // Apply 2-opt swap
    while (pos1 < pos2) {
        std::swap(newPath[pos1], newPath[pos2]);
        pos1++;
        pos2--;
    }
    p.setCitiesList(newPath);
    p.calculateCost(g);
    return p;
}


Path Genetic::generateRandomPath() {
    Path p(numOfCities);

    // Initialize the cities list in Path p
    int* cities = new int[numOfCities];
    for (int i = 0; i < numOfCities; ++i) {
        cities[i] = i;
    }


    // Shuffle the cities list
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cities, cities + numOfCities, gen);

    p.setCitiesList(cities);
    p.calculateCost(g);
    delete[] cities;
    return p;
}

void Genetic::printCurrentList() {
    for( int i = 0; i < currentNumOfPaths; i++){
//        listOfPaths[i].calculateCost(g);
        std::cout<<listOfPaths[i].to_string() <<"    COST: " << listOfPaths[i].getCost();

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

Path Genetic::getBestPath() const {
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

     for(int i =0; i< populationSize; i++){
         delete[] listOfPaths[i].getCitiesList();
     }

     delete []listOfPaths;

}

Path Genetic::generateGreedyPath() {
    Path greedyPath(numOfCities); // Inicjalizacja obiektu ścieżki

    int *citiesList = new int[numOfCities];

    bool *visited = new bool[numOfCities]; // Tablica odwiedzonych miast
    for (int i = 0; i < numOfCities; ++i) {
        visited[i] = false; // Inicjalizacja wszystkich miast jako nieodwiedzone
    }

    int currentCity = 0; // Początkowe miasto

    for (int i = 0; i < numOfCities; ++i) {
        int nextCity = -1;
        int minCost = INT_MAX;

        visited[currentCity] = true; // Oznacz bieżące miasto jako odwiedzone
        citiesList[i] = currentCity; // Dodaj bieżące miasto do ścieżki

        for (int j = 0; j < numOfCities; ++j) {
            if (!visited[j] && matrix[currentCity][j] < minCost) {
                minCost = matrix[currentCity][j];
                nextCity = j;
            }
        }

        if (nextCity != -1) {
            currentCity = nextCity; // Przejście do następnego miasta
        }
    }

    greedyPath.setCitiesList(citiesList); // Ustaw listę miast w obiekcie Path
    greedyPath.calculateCost(g);

    delete[] visited; // Zwolnienie zaalokowanej pamięci dla tablicy odwiedzonych miast
    delete[] citiesList;

    return greedyPath; // Zwróć ścieżkę
}

void Genetic::printBestPath() {
     std::cout<<bestPath.to_string();
 }



