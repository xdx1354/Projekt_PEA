//
// Created by stani on 25.10.2023.
//

#include <iostream>
#include "Menu.h"
#include "../data_structures/Graph.h"
#include "../tests/AutoTests.h"
#include "../algorithms/TS.h"
#include "Time.h"


void Menu::start() {


    string choose = "0";
    bool isGraphLoaded = false;



    while(choose != "-1"){

        std::cout<<"=====MENU=====\n";
        std::cout<<"1. Load data\n";
        std::cout<<"2. Print graph\n";
        std::cout<<"3. Perform Tabu Search algorithm\n";
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
                    runTS();
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
//                autoTests.autoTestBF();
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




void Menu::runTS(){

}