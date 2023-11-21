//
// Created by stani on 29.10.2023.
//

#include <fstream>
#include "iostream"
#include "AutoTests.h"
#include "../data_structures/Graph.h"
#include "../utils/Time.h"

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
//void AutoTests::autoTestBB() {
//
////    int quantities[12] = {5, 6, 7, 9,10, 12, 14, 16, 18, 20 ,22, 24};  // fixed list of tested quantities
//
//    int quantities[3] = {17, 5, 6};  // fixed list of tested quantities
//    for( int q: quantities){
//        string loc = R"(..\data\)";
//        string path = loc + "data" + to_string(q) + ".txt";
//        long long results[NUMBER_OF_TESTS] = {0};
//        long double avg = 0;
//
//
//        stats<<"BB: " <<q<<";";
//
//
//        for(int i = 0; i < NUMBER_OF_TESTS; i++){
//            // initialization of required objects
//            generateData(q);                        // generating new set of random data for this iteration
//            Graph g;
//            g.loadData(path);
//            BB bb(g);
//            Time time;
//
//            // algorithm time measurement
//            time.start();
//            bb.recursion(0);                        // calling just calculating method without printing result
//            time.stop();
//
//            // saving data into array
//            results[i] = time.returnTime();
//            stats<<results[i]<<";";
//            cout<<"Auto test BB. Size: "<< q <<"Try: "<<i<<"/20. Result "<<time.returnTime()<<"\n";
//
//            avg += (1.0/NUMBER_OF_TESTS) * results[i];          // calculating avg time
//        }
//
//        stats<<"\n";
//        cout<<"AVG TIME TAKEN: " << avg <<"\n";
//        cout<<"=======================================================================\n";
//
//
//
  //  }

//}
