//
// Created by stani on 25.10.2023.
//

#include <iostream>
#include "Menu.h"
#include "../data_structures/Graph.h"
#include "../tests/AutoTests.h"
#include "../algorithms/TS.h"
#include "Time.h"
#include "../algorithms/Genetic.h"


void Menu::start() {


    string choose = "0";
    bool isGraphLoaded = false;



    while(choose != "-1"){

        std::cout<<"=====MENU=====\n";
        std::cout<<"1. Load data\n";
        std::cout<<"2. Print graph\n";
        std::cout<<"3. Perform Tabu Search algorithm\n";
        std::cout<<"4. Perform genetic algorithm\n";
        std::cout<<"6. Generate data sets\n";
        std::cout<<"7. Autotests\n";
        std::cout<<"8. Exit\n";
        std::cout<<"Choose what do you want to do: ";

        std::cin>>choose;
        std::cout<<"\n\n";
        int integer_val;
        try{
             integer_val = stoi(choose);
        }
        catch(const invalid_argument &e) {
            integer_val = 0;
        }

        switch(integer_val){
            case 1:{
                std::string filename;
                std::cout<<"Program will be looking for the file in subdirectory /data.\n";
                std::cout<<"Type name of the file: ";
                std::cin>>filename;
                if(g.loadData(filename)){
                    isGraphLoaded = true;
                }else{
                    isGraphLoaded = false;
                }

                break;

            }
            case 2:{
                if( isGraphLoaded){
                    g.printGraph();
                }
                else{
                    std::cout<<"\nFirst you need to load graph. Choose 1.\n";
                }
                break;
            }
            case 3:{
                if( isGraphLoaded){
                    int endCondition = 0;
                    float q1;
                    cout<<"\nHow many iterations should algorithm perform? Type:   ";
                    cin >> endCondition;
                    cout<<"\nChoose probability of using first method of generating neighbour result (Swapping two cities in path). \n"
                          "Probability of reversing path between two cities will be calculated as reaming to 1.0.\n"
                          "Type number in range of 0.0 to 1.0:   ";
                    cin >> q1;

                    runTS(endCondition, q1, 1.0-q1);
                }
                else{
                    std::cout<<"\nFirst you need to load graph. Choose 1.\n";
                }
                break;
            }

            case 4:{

                if( isGraphLoaded){
                    string whatParams;

                    std::cout<<"\n 1. Run with predefined, universal parameters."
                               "\n 2. Run with custom parameters";
                    std::cin>>whatParams;

                    switch(stoi(whatParams)){
                        case 1:{

                            runGenetic(100000, 20, 20, 20, 20, 100);        // TODO: fill with optimal data after tests

                            break;
                        }
                        case 2:{
                            int iterations, population, cross, mutate, cross2, mutate2;

                            cout<<"\nChoose number of iterations: ";
                            cin>>iterations;
                            cout<<"\nChoose number size of population: ";
                            cin>>population;
                            cout<<"\nChoose number of crossing operations (swap to nodes) per epoch: ";
                            cin>>cross;
                            cout<<"\nChoose number of crossing2 operations (2opt) per epoch: ";
                            cin>>cross2;
                            cout<<"\nChoose number of mutate operations (half from A, filling from B in order of appearing) per epoch: ";
                            cin>>mutate;
                            cout<<"\nChoose number of mutate operations \n(raw part from A paste in the same place,"
                                  " filling with B, legalized using mapping) per epoch: ";
                            cin>>mutate2;
//                            runGenetic(100000, 20, 20, 20, 20, 100);
                            runGenetic(iterations, cross, mutate, cross2, mutate2, population);
                            break;
                        }
                        default:{
                            cout<<"\nWrong input, try again \n";
                            break;
                        }
                    }

                    break;
                }
                else{
                    std::cout<<"\nFirst you need to load graph. Choose 1.\n";
                }
                break;


            }

            case 6:{
                std::cout<<"Generates data sets of sizes from range 5 to 15 nodes.\n";
                std::cout<<"Files can by loaded from menu by choosing 1st option and typing name\n";
                std::cout<<"dataX where X is the number of nodes ex. data10\n";
                std::cout<<"Adding .txt extension is optional\n";
                AutoTests at;
                at.generateAllData();
                std::cout<<"Files generated.\n";

                break;
            }
            case 7:{
                AutoTests autoTests;
                std::cout<<"=======================================================================================";
                std::cout<<"TESTING TABU SEARCH:";
                autoTests.finalTests();
                std::cout<<"=======================================================================================";
                std::cout<<"\nTESTS FINISHED\n";
                std::cout<<"=======================================================================================";
                std::cout<<"\nPress any key to exit to menu\n";
                std::string a;
                std::cin >> a;
                break;

            }
            case 8:{
                choose = "-1";
                break;
            }
            default:{
                std::cout<<"Wrong input. Try again: ";
                choose = "0";
                break;
            }

        }

    }

}




void Menu::runTS(int endCon, float q1, float q2){
    TS ts(g);
    ts.apply(endCon, q1, q2);
    ts.printResult();
}

void Menu::runGenetic(int endCon, int crossCount, int mutateCount, int crossCount2, int mutateCount2, int sizeOfPopulation){
    Genetic gen(g, endCon, sizeOfPopulation, crossCount, mutateCount, crossCount2, mutateCount2);
    gen.apply();
}