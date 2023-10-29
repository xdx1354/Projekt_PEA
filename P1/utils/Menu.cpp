//
// Created by stani on 25.10.2023.
//

#include <iostream>
#include "Menu.h"
#include "../data_structures/Graph.h"


void Menu::start() {

    // structures




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
                //  another menu for autotests
                // Autotest will be called from here

            }
            default:{
                std::cout<<"Wrong input. Try again: ";
            }

        }



    }


//    Menu::run_BF(Graph g){
//
//    }

}
