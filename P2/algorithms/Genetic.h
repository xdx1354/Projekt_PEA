//
// Created by stani on 23.12.2023.
//

#ifndef P2_GENETIC_H
#define P2_GENETIC_H


class Genetic {




public:

    void apply(int numOfIterations);
    int getCurrentNumOfPaths() const;

    void setCurrentNumOfPaths(int currentNumOfPaths);

    void setListOfPaths(int **listOfPaths);

    void setBestPathFound(int *bestPathFound);

    void setBestCost(int bestCost);

    int **getListOfPaths() const;

    int *getBestPathFound() const;

    int getBestCost() const;

private:
    int currentNumOfPaths;          // number of currently stored paths in listOfPaths
    int **listOfPaths;              // [X][10] - X must fit whole population and additional path developed in current epoch
                                    // therefore it has to be calculated in constructor
    int *bestPathFound;
    int bestCost;

    int populationSize;             // number of paths at the beginning of each epoch
    int pathsListSize;              // X

    int crossCount;
    int mutateCount;


    /// constructor/destructor
    Genetic(int numOfIterations,  int sizeOfPopulation, int probabilityOfCross, int probabilityOfMutation );
    ~Genetic();

    /// method responsible for main logic of algo
    void epoch(int currentIteration);

    /// genetic operations
    int* cross(int A, int B);       // takes half of A and fills with B
    int* mutate(int A);             // swaps two cities


    ///utility methods
    void picTopResults();           // it will sort and then save only top 10 results
    int* generateRandomPath();      // might be changed later to improve algo


};


#endif //P2_GENETIC_H
