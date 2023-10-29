//
// Created by stani on 29.10.2023.
//

#include <fstream>
#include "iostream"
#include "AutoTests.h"
#include "../data_structures/Graph.h"
#include "../algorithms/BB.h"
#include "../utils/Time.h"

using namespace std;

/**
 * Generating data for auto tests for fixed range of sizes (5 - 20) of graphs.
 * Creates several .txt files in directory /data.
 * Name of file is generated following the rule: dataX.txt where X is number of nodes of this graph
 *
 */
void AutoTests::generateAllData() {

    // defying graphs sizes
    int quantities[16] = {5, 6, 7, 8, 9,10, 11,12, 13, 14, 15, 16, 17, 18, 19, 20};

    for(int i = 0; i < size(quantities); i++){

        ofstream file;
        file.open("data" + to_string(quantities[i]) + ".txt");
        file<<i<<"\n";                                              // loading first line with number of nodes

        for(int u = 0; u < i; u++){
            for( int v = 0; v < i; v++){

                if(u == v){
                    file<<"0 ";
                }
                else{
                    srand(time(NULL));
                    int randNum = rand()%100 + 1;                   // rand number from range of <1, 101>
                    file<<randNum<<" ";
                }

            }
            file<<"\n";
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
    file.open("data" + to_string(size) + ".txt");
    file<<size<<"\n";                                              // loading first line with number of nodes

    for(int u = 0; u < size; u++){
        for( int v = 0; v < size; v++){

            if(u == v){
                file<<"0 ";
            }
            else{
                srand(time(NULL));
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
void AutoTests::autoTestBB() {

    int quantities[5] = {5, 6, 7, 10, 12};  // fixed list of tested quantities

    for( int q: quantities){
        string path = ("data" + to_string(q) + ".txt");      //TODO: later data will be in subdir /data so need to change path
        long long results[NUMBER_OF_TESTS] = {0};
        long long avg = 0;


        for(int i = 0; i < NUMBER_OF_TESTS; i++){
            // initialization of required objects
            generateData(q);                        // generating new set of random data for this iteration
            Graph g;
            g.loadData(path);
            BB bb(g);
            Time time;

            // algorithm time measurement
            time.start();
            bb.recursion(0);
            time.stop();

            // saving data into array
            results[i] = time.returnTime();
            cout<<"Auto test BB. Size: "<< q <<"Try: "<<i<<"/20. Result "<<time.returnTime()<<"\n";

            avg += 1/NUMBER_OF_TESTS * results[i];          // calculating avg time
        }

        cout<<"AVG TIME TAKEN: " << avg <<"\n";
        cout<<"=======================================================================\n";

        // delete g;    TODO: create destructor for graph class

    }



}