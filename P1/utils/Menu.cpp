//
// Created by stani on 25.10.2023.
//

#include <iostream>
#include "Menu.h"
#include "../data_structures/Graph.h"


void Menu::start() {

    // structures




    int choose = 0;



    while(choose != -1){

        std::cout<<"MENU";
        std::cout<<"1. Load data";
        std::cout<<"2. Print graph";
        std::cout<<"3. Perform Brut Force algorithm";
        std::cout<<"4. Perform Branch and Bound algorithm";
        std::cout<<"5. Perform Dynamic programing algorithm";
        std::cout<<"6. Measure times of algorithms";
        std::cout<<"9. Exit";
        std::cout<<"Choose what do you want to do: ";

        std::cin>>choose;

        switch(choose){
            case 1:{
                std::string filename;
                std::cout<<"Type name of the file: ";
                std::cin>>filename;
                g.loadData(filename);
            }
            case 2:{
                g.printGraph();
            }
            case 3:{
                run_BF(g);
            }
            case 4:{
                run_BB(g);
            }

            case 5:{
                run_DP(g);
            }
            case 6:{
                measure_time();
            }
            case 9:{

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
