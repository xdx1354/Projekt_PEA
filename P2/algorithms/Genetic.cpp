//
// Created by stani on 23.12.2023.
//

#include "Genetic.h"
#include "iostream"
#include <algorithm>
//#include <iterator>
//#include <random>


Genetic::Genetic(Graph graph, int numOfIterations, int sizeOfPopulation, int crossCount, int mutateCount, int cross2Count, int mutate2Count)
        : bestPath(bestPath) {

    srand(time(NULL));

    g = graph;
    matrix = g.getMatrix();
    numOfCities = g.getSize();

    currentNumOfPaths = 0;
    pathsListSize = sizeOfPopulation + crossCount + cross2Count + mutateCount + mutate2Count;
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
    for(int i = 0; i < populationSize; i++){
        listOfPaths[i] = generateRandomPath();
        listOfPaths[i].calculateCost(g);

    }
    currentNumOfPaths = populationSize;

    std::cout<<"Rand paths generated\n";


    //main loop iterating through epochs
    for(int i = 0; i < numOfIterations; i++){
        epoch(i);
    }

    pickTopResults();
    std::cout<<"\nAFTER\n";
    printCurrentList();
//    std::cout<<"\nAFTER v2\n";
//    printCurrentList();

    std::cout<<"Cheapest ever path cost: " <<bestCost<<"\n";
    std::cout<<"Cheapest path cost: " <<listOfPaths[0].getCost()<<"\n";
    std::cout<<"2nd cheapest path cost: " <<listOfPaths[1].getCost()<<"\n";
}

void Genetic::epoch(int currentIteration) {

//    for(int i = 0; i < crossCount; i++){
//
//        int first, second;
//        do{
//            first = rand() % (populationSize/2);
//            second = rand() % (populationSize/2);
//        } while (first == second);
//
//
//        std::tuple<Path, Path> crossResult = cross2(listOfPaths[first], listOfPaths[second]);
//        listOfPaths[currentNumOfPaths] = std::get<0>(crossResult);
//        currentNumOfPaths++;
//        listOfPaths[currentNumOfPaths] = std::get<1>(crossResult);
//        currentNumOfPaths++;
//    }


    for(int i = 0; i < mutateCount; i++){

        listOfPaths[currentNumOfPaths] = mutate(listOfPaths[rand() % (populationSize / 2)]);
        currentNumOfPaths++;

    }

//    std::cout<<"Epoch: " + std::to_string(currentIteration) <<"\n";
//    printCurrentList();
//    std::cout<<"\n\n";

    pickTopResults();

}

void Genetic::pickTopResults() {
    int bestCurrentCost = INT_MAX;

    // calculate current costs TODO: this should be done while adding a new path to save time

//    /// THIS IS JUST A HOTFIX
//    for(int i = 0; i < currentNumOfPaths; i++){
//        listOfPaths[i].calculateCost(g);
//    }

    std::cout<<"\n\n\nBEFORE SORTING\n";
    printCurrentList();

//    // bubble sort
//    for (int i = 0; i < currentNumOfPaths - 1; i++) {
//        for (int j = 0; j < currentNumOfPaths - i - 1; j++) {
//            if (listOfPaths[j].getCost() > listOfPaths[j + 1].getCost()) {
//                std::swap(listOfPaths[j], listOfPaths[j + 1]);
//
//            }
//        }
//    }
    std::sort(listOfPaths, listOfPaths + currentNumOfPaths, [](const Path& a, const Path& b) {
        return a.getCost() < b.getCost(); // Sort in ascending order of cost
    });

//    std::vector<Path> vec;
//    for(int i = 0; i < populationSize)


    std::cout<<"\n\n\nAFTER SORTING\n";
    printCurrentList();
    // check if new best result found
    bestCurrentCost = listOfPaths[0].getCost();
    if (bestCurrentCost < bestCost) {
        bestCost = bestCurrentCost;
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

    // Take the first half of cities from Path A
    for (int i = 0; i < numOfCities / 2; i++) {
        newPathA[i] = A.getCitiesList()[i];
        counterA++;
    }

    // Fill the remaining cities from Path B to form newObjPathA
    for (int i = 0; i < numOfCities; i++) {
        int potentialCity = B.getCitiesList()[i];
        bool isPresent = false;

        // Check if the city is already present in the first half of newPathA
        for (int j = 0; j < numOfCities / 2; j++) {
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

    // Take the first half of cities from Path B
    for (int i = 0; i < numOfCities / 2; i++) {
        newPathB[i] = B.getCitiesList()[i];
        counterB++;
    }

    // Fill the remaining cities from Path A to form newObjPathB
    for (int i = 0; i < numOfCities; i++) {
        int potentialCity = A.getCitiesList()[i];
        bool isPresent = false;

        // Check if the city is already present in the first half of newPathB
        for (int j = 0; j < numOfCities / 2; j++) {
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
 * Takes part of path A and rest of elemgents from B to form A'. Then by applying mapping legalizes the path.
 * To create B', takes part of B and fills rest with nodes from A, then applies mappin
 * @param A Path - first parent
 * @param B Path - second parent
 * @return Tuple of two objects Path
 */
std::tuple <Path, Path> Genetic::cross2(Path A, Path B){
    Path aPrim(numOfCities);
    Path bPrim(numOfCities);

    int *aPrimList = new int[numOfCities];
    int *bPrimList = new int[numOfCities];

    int *aList = A.getCitiesList();
    int *bList = B.getCitiesList();

    /// ALGORITHM LOGIC

    int aBegin, aEnd, bBegin, bEnd;         // beginnings and ends of copied part from A/B to aPrim/bPrim

    // pick random positions and make them in proper order
    aBegin = rand()%numOfCities;
    aEnd = rand()%numOfCities;

    bBegin = rand()%numOfCities;
    bEnd = rand()%numOfCities;

    if(aBegin > aEnd){
        std::swap(aBegin, aEnd);
    }
    if(bBegin > bEnd){
        std::swap(bBegin, bEnd);
    }


    // Copying part of A and B to A' and B'
    for (int i = 0; i < numOfCities; i++) {
        // Logic for aPrimList
        if (i >= aBegin && i < aEnd) {
            aPrimList[i] = aList[i];
        } else {
            // Store elements from B that are not already in A'
            int currentElement = bList[i];
            bool isDuplicate = false;

            // Check if the element from B already exists in A'
            for (int j = aBegin; j < aEnd; j++) {
                if (aList[j] == currentElement) {
                    isDuplicate = true;
                    break;
                }
            }

            if (!isDuplicate) {
                aPrimList[i] = bList[i];
            } else {
                // If the element from B already exists in A', find a suitable replacement from A
                for (int j = 0; j < numOfCities; j++) {
                    bool foundInBPrim = false;

                    // Check if the element from A already exists in B'
                    for (int k = bBegin; k < bEnd; k++) {
                        if (bList[k] == aList[j]) {
                            foundInBPrim = true;
                            break;
                        }
                    }

                    if (!foundInBPrim) {
                        aPrimList[i] = aList[j];
                        break;
                    }
                }
            }
        }

        // Logic for bPrimList
        if (i >= bBegin && i < bEnd) {
            bPrimList[i] = bList[i];
        } else {
            // Store elements from A that are not already in B'
            int currentElement = aList[i];
            bool isDuplicate = false;

            // Check if the element from A already exists in B'
            for (int j = bBegin; j < bEnd; j++) {
                if (bList[j] == currentElement) {
                    isDuplicate = true;
                    break;
                }
            }

            if (!isDuplicate) {
                bPrimList[i] = aList[i];
            } else {
                // If the element from A already exists in B', find a suitable replacement from B
                for (int j = 0; j < numOfCities; j++) {
                    bool foundInAPrim = false;

                    // Check if the element from B already exists in A'
                    for (int k = aBegin; k < aEnd; k++) {
                        if (aList[k] == bList[j]) {
                            foundInAPrim = true;
                            break;
                        }
                    }

                    if (!foundInAPrim) {
                        bPrimList[i] = bList[j];
                        break;
                    }
                }
            }
        }
    }




    aPrim.setCitiesList(aPrimList);
    aPrim.calculateCost(g);
    bPrim.setCitiesList(bPrimList);
    bPrim.calculateCost(g);

    return std::make_tuple(aPrim,bPrim);
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

    return p;
}

void Genetic::printCurrentList() {
    for( int i = 0; i < currentNumOfPaths; i++){
        listOfPaths[i].calculateCost(g);
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
