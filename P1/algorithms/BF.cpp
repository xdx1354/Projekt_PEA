//
// Created by stani on 14.10.2023.
//

#include "BF.h"

BF::~BF() {
        delete []visited;
}

BF::BF(Graph graph){
    numOfCities = graph.getSize();      // setting the value of filed
    matrix = graph.getMatrix();         // extracted 2D array from graph class
    visited = new bool[numOfCities];    // list of currently visited cities
    best_cost = INT_MAX;                // minimal cost of checked paths (currently set as maximal integer value)
    current_cost = 0;                   // cost of current path

    // setting the list elements to false
    for(int i=0; i<numOfCities; i++){
        visited[i] = false;
    }
}


/**
 * Recursive function looking for cheapest hamiltonian cycle in given graph
 * @param node : node from which this functions begins
 */
void BF::recursion(int node){

    path.push_back(node);
    path_len++;

    if(path_len != numOfCities){                        // if we did not reach 10 cities
        visited[node] = true;                         // marking current node as visited
        for (int u = 0; u < numOfCities; u++){          // iterating through all vertexes
            if (visited[u])                             // if this node was already visited we skip it
                continue;

            current_cost += matrix[node][u];          // adding cost of traveling to next node
            recursion(u);                         // calling this function but whith the next node as a starting
            current_cost -= matrix[node][u];          // subtracting cost of travel on the way back
        }

        visited[node] = false;                        // marking the node as not visited on the way back
        path_len--;                                     // keeping the paht_len right
        path.pop_back();                                // pop_back the node from stack

    }
    else if (matrix[node][0] <= 0){                   // in this case we came back to starting node
        path_len--;                                     // going back to the previous
        path.pop_back();
    }
    else{
        current_cost += matrix[node][0];              // in this case we finally got cycle through all the ten cities

        if (current_cost >= best_cost){                 // checking if it's worse/equal to the best one
            current_cost -= matrix[node][0];          // if it is we will back off from it
        }
        else{                                           // in this case it is better
            best_cost = current_cost;                   // so we change the value and copy the path
            best_path.clear();
//            for(const int& i : path)
//                best_path.push_back(i);
            best_path = path;
            current_cost -= matrix[node][0];          // preparation for going back
        }
        path_len--;                                     // going back to previous city
        path.pop_back();
    }
}


/**
 * Printing function.
 */
void BF::printResult() {
    std::cout<<"Best path cost: " << best_cost << std::endl;

    if(best_path.empty())
        printf("\nHamiltonian path doesn't exist.");
    else {
        printf("Shortest path:\n");
        for(int i:best_path){
            cout<<i<<", ";
        }
        std::cout<<"0";
        std::cout << std::endl;
        std::cout << std::endl;
    }

}

void BF::run(){
    recursion(0);
    printResult();
}



