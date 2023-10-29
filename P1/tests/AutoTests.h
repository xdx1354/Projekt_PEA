//
// Created by stani on 29.10.2023.
//

#ifndef P1_AUTOTESTS_H
#define P1_AUTOTESTS_H
#define NUMBER_OF_TESTS 20

class AutoTests {

public:
    void generateAllData();        //generating data for autotests. Set for specific sizes of graphs

    // auto test based on generated data. Include time measurement. Calculates avg time of x repetitions for each quantity
    void autoTestBF();
    void autoTestBB();
    void autoTestDP();


    void generateData(int size);
};


#endif //P1_AUTOTESTS_H
