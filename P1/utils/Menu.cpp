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

        std::cout<<"=====MENU=====\n";
        std::cout<<"1. Load data\n";
        std::cout<<"2. Print graph\n";
        std::cout<<"3. Perform Brut Force algorithm\n";
        std::cout<<"4. Perform Branch and Bound algorithm\n";
        std::cout<<"5. Perform Dynamic programing algorithm\n";
        std::cout<<"6. Measure times of algorithms\n";
        std::cout<<"9. Exit\n";
        std::cout<<"10. Autotests\n";
        std::cout<<"Choose what do you want to do: ";

        std::cin>>choose;
        std::cout<<"\n\n";

        switch(choose){
            case 1:{
                std::string filename;
                std::cout<<"Program will be looking for the file in subdirectory /data.\n";
                std::cout<<"Type name of the file: ";
                std::cin>>filename;
                g.loadData(filename);
                isGraphLoaded = true;
                break;

            }
            case 2:{
                if( isGraphLoaded){
                    g.printGraph();
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }
                break;
            }
            case 3:{
                if( isGraphLoaded){
                    run_BF();
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }
                break;
            }
            case 4:{
                if( isGraphLoaded){
                    run_BB();
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }
                break;
            }

            case 5:{
                if( isGraphLoaded){
                    run_DP();
                }
                else{
                    std::cout<<"First you need to load graph. Choose 1.";
                }
                break;
            }
            case 6:{
                break;
            }
            case 9:{
                choose = -1;
                break;
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
//                autoTests.autoTestDP();
                std::cout<<"=======================================================================================";
                std::cout<<"\nTESTS FINISHED\n";
                std::cout<<"=======================================================================================";
                std::cout<<"\nPress any key to exit to menu\n";
                std::string a;
                std::cin >> a;
                break;

            }
            default:{
                std::cout<<"Wrong input. Try again: ";
                break;
            }

        }

    }

}

void Menu::run_BF(){
    // graph is a field of this class
    // at this point graph is already loaded with data

    BF bf(g);
    bf.run();

}


void Menu::run_BB(){
    // graph is a field of this class
    // at this point graph is already loaded with data

    BB bb(g);
    bb.run();

}


void Menu::run_DP(){
    // graph is a field of this class
    // at this point graph is already loaded with data

    DP dp(g);
    dp.run();

}
