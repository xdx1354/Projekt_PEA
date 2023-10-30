//
// Created by stani on 25.10.2023.
//

#include <iostream>
#include "Menu.h"
#include "../data_structures/Graph.h"
#include "../tests/AutoTests.h"
#include "../algorithms/BB.h"
#include "../algorithms/BF.h"
#include "../algorithms/DP.h"


void Menu::start() {


    int choose = 0;
    bool isGraphLoaded = false;



    while(choose != -1){

        std::cout<<"MENU";
        std::cout<<"1. Load data";
        std::cout<<"2. Print graph";
        std::cout<<"3. Perform Brut Force algorithm";
        std::cout<<"4. Perform Branch and Bound algorithm";
        std::cout<<"5. Perform Dynamic programing algorithm";
        std::cout<<"6. Measure times of algorithms";
        std::cout<<"9. Exit";
        std::cout<<"10. Autotests";
        std::cout<<"Choose what do you want to do: ";

        std::cin>>choose;

        switch(choose){
            case 1:{
                std::string filename;
                std::cout<<"Program will be looking for the file in subdirectory /data.\n";
                std::cout<<"Type name of the file: ";
                std::cin>>filename;
                g.loadData(filename);
                isGraphLoaded = true;

            }
            case 2:{
                if( isGraphLoaded){
                    g.printGraph();
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }
            }
            case 3:{
                if( isGraphLoaded){
                    run_BF(g);
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }

            }
            case 4:{
                if( isGraphLoaded){
                    run_BB(g);
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }
            }

            case 5:{
                if( isGraphLoaded){
                    run_DP(g);
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }
            }
            case 6:{

            }
            case 9:{

            }
            case 10:{
                AutoTests autoTests;
                std::cout<<"=======================================================================================";
                std::cout<<"TESTING BRUT FORCE:";
                autoTests.autoTestBF();
                std::cout<<"=======================================================================================";
                std::cout<<"TESTING BRANCH AND BOUND:";
                autoTests.autoTestBB();
                std::cout<<"=======================================================================================";
                std::cout<<"TESTING DYNAMIC PROGRAMMING:";
                autoTests.autoTestDP();
                std::cout<<"=======================================================================================";
                std::cout<<"TESTS FINISHED";
                std::cout<<"=======================================================================================";
                std::cout<<"Press any key to exit to menu";
                std::string a;
                std::cin >> a;


            }
            default:{
                std::cout<<"Wrong input. Try again: ";
            }

        }



    }

}

void Menu::run_BF(){
    // graph is a field of this class
    // at this point graph is already loaded with data

    BF bf(g);
    bf.recursion(0);
    bf.print();

}


void Menu::run_BB(){
    // graph is a field of this class
    // at this point graph is already loaded with data

    BB bb(g);
    bb.recursion(0);
    bb.print();

}


void Menu::run_DP(){
    // graph is a field of this class
    // at this point graph is already loaded with data

    DP dp(g);
    dp.apply();
    dp.getResult();

}
