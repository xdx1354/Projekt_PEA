//
// Created by stani on 29.10.2023.
//

#ifndef P1_AUTOTESTS_H
#define P1_AUTOTESTS_H
#define NUMBER_OF_TESTS 20

class AutoTests {
    std::ofstream stats;           // ofstream for writting results of autotest to .txt file

public:
    void generateAllData();        //   generating data for autotests. Set for specific sizes of graphs. Array of sizes is hardcoded
    void generateData(int size);   // generates data of specified size graph
    // auto test based on generated data. Include time measurement. Calculates avg time of x repetitions for each quantity
    void autoTestBF();
    void autoTestBB();
    void autoTestDP();
    AutoTests();                   // constructors
    ~AutoTests();                  // destructor



    void comparisonTestsDP();
};


#endif //P1_AUTOTESTS_H
