//
// Created by stani on 29.10.2023.
//

#include <fstream>
#include "iostream"
#include "AutoTests.h"
#include "../data_structures/Graph.h"
#include "../algorithms/TS.h"
#include "../algorithms/Genetic.h"

using namespace std;

AutoTests::AutoTests(){
    string loc = "..\\results\\";
    stats.open(loc + "stats.txt");            // opening the ofstream to file
}

AutoTests::~AutoTests() {
    stats.close();                              // closing the ofstream to file
}

/**
 * Generating data for auto tests for fixed range of sizes (5 - 20) of graphs.
 * Creates several .txt files in directory /data.
 * Name of file is generated following the rule: dataX.txt where X is number of nodes of this graph
 *
 */
void AutoTests::generateAllData() {

    // Defining graph sizes
    int quantities[16] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    // Seed the random number generator once outside the loop
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < 16; i++) {

        ofstream file;
        string loc = "..\\data\\";
        file.open(loc + "data" + to_string(quantities[i]) + ".txt");
        file << quantities[i] << "\n";                                 // Loading the first line with the number of nodes

        for (int u = 0; u < quantities[i]; u++) {
            for (int v = 0; v < quantities[i]; v++) {

                if (u == v) {
                    file << "0 ";
                } else {
                    int randNum = rand() % 100 + 1;                   // rand number from range of <1, 101>
                    file << randNum << " ";
                }

            }
            file << "\n";
        }
        file.close();
    }
}
/**
 * Generating data for auto tests for single size of graph given as param.
 * Creates several .txt files in directory /data.
 * Name of file is generated following the rule: dataX.txt where X is number of nodes of this graph
 * @param size  size of graph that data will be generated
 */
void AutoTests::generateData(int size){
    ofstream file;
    string loc = "..\\data\\";
    file.open(loc + "data" + to_string(size) + ".txt");
    file<<size<<"\n";                                              // loading first line with number of nodes

    srand(static_cast<unsigned>(time(0)));

    for(int u = 0; u < size; u++){
        for( int v = 0; v < size; v++){

            if(u == v){
                file<<"0 ";
            }
            else{
                int randNum = rand()%100 + 1;                   // rand number from range of <1, 101>
                file<<randNum<<" ";
            }

        }
        file<<"\n";
    }
    file.close();
}

/*
 * Testing the Branch and Bound algorithm. Test are performed on list of fixed sized graphs for a fixed sized times.
 * For each test there is new data generated by generateData() method.
 */
void AutoTests::paramsTestsTS() {

    //{x,y,z}
    // x - probability of one swap
    // y - probability of two swaps
    // z - probability of shaking
    float proportions[5][2] = {{0.4, 0.6},
                               {0.6, 0.4},
                               {0.2, 0.8},
                               {0.8, 0.2},
                               {0.7, 0.3}};

    int quantities[3] = {20, 40, 80};
    const int lenQuantities = sizeof(quantities) / sizeof(quantities[0]);
    int numOfIterations[4] = {100, 10000, 100000, 1000000};
    const int lenIterations = sizeof(numOfIterations) / sizeof(numOfIterations[0]);

    for (int j = 0; j < lenQuantities; j++) {
        string loc = R"(..\data\)";
        string path = loc + "data" + to_string(quantities[j]) + ".txt";
        int results[NUMBER_OF_TESTS] = {0};
        float avg = 0;

        generateData(quantities[j]);
        stats << "TS: " << quantities[j] << ";\n";

        for (int i = 0; i < lenIterations; i++) {
            for (int p = 0; p < 5; p++) {
                stats << "Quantity: " << quantities[j] << ", Iterations: " << numOfIterations[i] << ", Proportions: " << proportions[p][0] << ", " << proportions[p][1] << "\n";
                for (int k = 0; k < NUMBER_OF_TESTS; k++) {
                    Graph g;
                    g.loadData(path);
                    TS ts(g);

                    ts.apply(numOfIterations[i], proportions[p][0], proportions[p][1]);
                    results[k] = ts.bestPathCost;
//                    stats << ts.bestPathCost << ";";
                    cout << "Auto test TS. Size: " << quantities[j] << " Try: " << k << "/19. Number of iterations: "
                         << numOfIterations[i] << " Result " << results[k] << "\n";
                    avg += (1.0 / NUMBER_OF_TESTS) * ts.bestPathCost; // calculating avg result
                }
                stats << avg << "\n";
                avg = 0;
            }
            stats << "\n";
        }
        cout << "AVG CALCULATED RESULT: " << avg << "\n";
        cout << "=======================================================================\n";
    }
}

void AutoTests::alphaTests(){

    float alpha[10] = {0.1 ,0.2, 0.3, 0.4, 0.5, 0.6, 0.75, 0.9, 1};


    for (float a : alpha){
        Graph g;
        g.loadData("wersja2");
        TS ts(g);
        ts.grasp(a);
        cout<<"Test alpha = " << a <<" Wynik: " <<ts.currentPathCost<< endl;
    }


}

void AutoTests::finalTests(){

    float proportions[2] ={0.8, 0.2};
    int quantities[6] = {20, 40, 80, 120 , 160, 200};
    const int lenQuantities = sizeof(quantities) / sizeof(quantities[0]);
    int numOfIterations[6] = {100, 10000, 50000, 100000, 1000000, 2000000};
    const int lenIterations = sizeof(numOfIterations) / sizeof(numOfIterations[0]);


    for (int j = 0; j < lenQuantities; j++) {

        generateData(quantities[j]);
        string loc = R"(..\data\)";
        string path = loc + "data" + to_string(quantities[j]) + ".txt";

        int results[NUMBER_OF_TESTS] = {0};
        float avg = 0;

        stats << "TS: " << quantities[j] << ";\n";

        for (int i = 0; i < lenIterations; i++) {

            stats  << "\n" << quantities[j] << ";" << numOfIterations[i] << "\n";

            for (int k = 0; k < NUMBER_OF_TESTS; k++) {

                Graph g;
                g.loadData(path);
                TS ts(g);

                ts.apply(numOfIterations[i], proportions[0], proportions[1]);

                results[k] = ts.bestPathCost;

                cout << "Auto test TS. Size: " << quantities[j] << " Try: " << k << "/19. Number of iterations: "
                     << numOfIterations[i] << " Result " << results[k] << "\n";
                avg += (1.0 / NUMBER_OF_TESTS) * ts.bestPathCost; // calculating avg result
            }
            stats << avg<<";";
            avg = 0;

        }
        cout << "AVG CALCULATED RESULT: " << avg << "\n";
        cout << "=======================================================================\n";
    }
}

/**
 * method performing specific test required for university raport
 */
void AutoTests::raportTests(){

    float proportions[2] ={0.8, 0.2};

    string fileNames[5] = {"tsp_10c", "tsp_14_db", "tsp_65", "tsp_171", "tsp_443"};
    int lenFileNames = 5;
    int numOfIterations[6] = {100, 10000, 50000, 100000, 1000000, 2000000};
    int bestRes = INT_MAX;

    for (int j = 0; j < lenFileNames; j++) {

        string loc = R"(..\data\)";
        string path = loc + fileNames[j] + ".txt";

        int results[NUMBER_OF_TESTS] = {0};
        float avg = 0;

        stats << "TS: " << fileNames[j] << ";\n";

        for (int i=0; i < 6; i++) {

            stats  << "\n" << fileNames[j] << ";" << numOfIterations[i] << "\n";

            for (int k = 0; k < NUMBER_OF_TESTS; k++) {

                Graph g;
                g.loadData(path);
                TS ts(g);

                ts.apply(numOfIterations[i], proportions[0], proportions[1]);

                if(bestRes > ts.bestPathCost){
                    bestRes = ts.bestPathCost;
                }

                cout << "Auto test TS. Size: " << fileNames[j] << " Try: " << k << "/19. Number of iterations: "
                     << numOfIterations << " Result " << results[k] << "\n";
            }
            stats << bestRes<<";";
            bestRes = INT_MAX;

        }
        cout << "AVG CALCULATED RESULT: " << avg << "\n";
        cout << "=======================================================================\n";
    }
}


void AutoTests::populationTestsGenetic() {

    std::ofstream tests;
    string res_loc = "..\\results\\";
    tests.open(res_loc + "population_tests.txt");            // opening the ofstream to file

    /// CROSS AND MUTATE VALUES ARE SET TO 1/10 OF THE SIZE OF POPULATION



    int populationSize[5] = {10, 100, 500, 1000, 5000};

    int quantities[4] = {20, 40, 80, 120};
    const int lenQuantities = sizeof(quantities) / sizeof(quantities[0]);
    int numOfIterations[4] = {100, 10000, 100000, 1000000};
    const int lenIterations = sizeof(numOfIterations) / sizeof(numOfIterations[0]);

    for (int j = 0; j < lenQuantities; j++) {
        string loc = R"(..\data\)";
        string path = loc + "data" + to_string(quantities[j]) + ".txt";
        int min = INT_MAX;

        generateData(quantities[j]);
        tests << "TS: " << quantities[j] << ";\n";

        for (int i = 0; i < lenIterations; i++) {
            for (int p = 0; p < 5; p++) {
                stats << "Quantity: " << quantities[j] << ", Iterations: " << numOfIterations[i] << ", Population: " << populationSize[i]  << "\n";
                for (int k = 0; k < NUMBER_OF_TESTS; k++) {
                    Graph g;
                    g.loadData(path);
                    int currentPopulation = numOfIterations[i];
                    Genetic gen(g, currentPopulation, quantities[j], currentPopulation/10, currentPopulation/10, currentPopulation/10, currentPopulation/10);
                    gen.apply();

                    if(gen.getBestCost() < min){
                        min = gen.getBestCost();
                    }
                    cout << "Auto test TS. Size: " << quantities[j] << " Try: " << k << "/19. Number of iterations: "
                         << numOfIterations[i] << " Result " << gen.getBestCost() << "\n";


                }
                tests << min << "\n";
            }
            tests << "\n";
        }
        cout << "BEST CALCULATED RESULT: " << min << "\n";
        cout << "=======================================================================\n";

        tests.close();
    }
}


void AutoTests::mutateTestsGenetic() {

    std::ofstream tests;
    string res_loc = "..\\results\\";
    tests.open(res_loc + "mutate_tests.txt");            // opening the ofstream to file

    /// CROSS AND MUTATE VALUES ARE SET TO 1/10 OF THE SIZE OF POPULATION

    int POPULATION = 100;
    int SIZE_OF_GRAPH = 20;
    int ITERATIONS = 10000;
    float CROSS_NUMBER = 0.1;

    float quantities[9][2]={
            {0.1, 0.1},
            {0.2, 0.2},
            {0.3, 0.3},
            {0.1, 0.2},
            {0.2, 0.1},
            {0.3, 0.1},
            {0.3, 0.2},
            {0.2, 0.3},
            {0.1, 0.3}
    };


    string loc = R"(..\data\)";
    string path = loc + "data100.txt";
    int min = INT_MAX;

    generateData(100);
    tests << "Genetic MUTATE " << 100 << ";\n";

    for (int p = 0; p < 9; p++) {
        stats << "Size of graph: " << SIZE_OF_GRAPH  << ", Iterations: " << ITERATIONS << ", Population: " << POPULATION  <<", proportions : "<<quantities[p][0]<<", "<< quantities[p][1]<< "\n";
        for (int k = 0; k < NUMBER_OF_TESTS; k++) {
            Graph g;
            g.loadData(path);
            Genetic gen(g, ITERATIONS, POPULATION, POPULATION*CROSS_NUMBER, POPULATION * quantities[p][0], POPULATION*CROSS_NUMBER, POPULATION * quantities[p][1]);
            gen.apply();

            if(gen.getBestCost() < min){
                min = gen.getBestCost();
            }
            cout << "Auto test genetic MUTATE. Size: " << SIZE_OF_GRAPH << " Try: " << k << "/19. Proportions: "
                 << quantities[p][0]<<", "<< quantities[p][1]<< " Result " << gen.getBestCost() << "\n";


        }
        tests << min << "\n";

        cout << "BEST CALCULATED RESULT: " << min << "\n";
        cout << "=======================================================================\n";
    }


        tests.close();

}

void AutoTests::crossTestsGenetic() {

    std::ofstream tests;
    string res_loc = "..\\results\\";
    tests.open(res_loc + "cross_tests.txt");            // opening the ofstream to file

    /// CROSS AND MUTATE VALUES ARE SET TO 1/10 OF THE SIZE OF POPULATION

    int POPULATION = 100;
    int SIZE_OF_GRAPH = 20;
    int ITERATIONS = 10000;
    float MUTATE_NUMBER = 0.1;

    float quantities[9][2]={
            {0.1, 0.1},
            {0.2, 0.2},
            {0.3, 0.3},
            {0.1, 0.2},
            {0.2, 0.1},
            {0.3, 0.1},
            {0.3, 0.2},
            {0.2, 0.3},
            {0.1, 0.3}
    };


    string loc = R"(..\data\)";
    string path = loc + "data100.txt";
    int min = INT_MAX;

    generateData(100);
    tests << "Genetic CROSS " << 100 << ";\n";

    for (int p = 0; p < 9; p++) {
        stats << "Size of graph: " << SIZE_OF_GRAPH  << ", Iterations: " << ITERATIONS << ", Population: " << POPULATION  <<", proportions : "<<quantities[p][0]<<", "<< quantities[p][1]<< "\n";
        for (int k = 0; k < NUMBER_OF_TESTS; k++) {
            Graph g;
            g.loadData(path);
            Genetic gen(g, ITERATIONS, POPULATION, POPULATION * quantities[p][0], POPULATION*MUTATE_NUMBER, POPULATION * quantities[p][1], POPULATION*MUTATE_NUMBER);
            gen.apply();

            if(gen.getBestCost() < min){
                min = gen.getBestCost();
            }
            cout << "Auto test genetic CROSS. Size: " << SIZE_OF_GRAPH << " Try: " << k << "/19. Proportions: "
                 << quantities[p][0]<<", "<< quantities[p][1]<< " Result " << gen.getBestCost() << "\n";


        }
        tests << min << "\n";

        cout << "BEST CALCULATED RESULT: " << min << "\n";
        cout << "=======================================================================\n";
    }


    tests.close();

}
