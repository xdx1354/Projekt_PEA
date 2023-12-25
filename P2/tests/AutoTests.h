//
// Created by stani on 29.10.2023.
//

#ifndef P1_AUTOTESTS_H
#define P1_AUTOTESTS_H
#define NUMBER_OF_TESTS 20

class AutoTests {
    std::ofstream stats;           // ofstream for writting results of autotest to .txt file

public:
    void generateAllData();         // generating data for autotests. Set for specific sizes of graphs. Array of sizes is hardcoded
    void generateData(int size);    // generates data of specified size graph

    void paramsTestsTS();             // testing parameters q1, q2 for optimising  the algorithm - evaluated in paper
    void alphaTests();              // testing parameter alpha
    void finalTests();              // finalTests of algorithm, with optimised parameters
    AutoTests();                    // constructors
    ~AutoTests();                   // destructor

    void raportTests();

    void populationTestsGenetic();

    void mutateTestsGenetic();

    void crossTestsGenetic();
};


#endif //P1_AUTOTESTS_H
