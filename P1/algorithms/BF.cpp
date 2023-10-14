//
// Created by stani on 14.10.2023.
//



#include "BF.h"

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
 * @param vertex : vertex from which this functions begins
 */
void BF::recursion(int vertex){

    path.push_back(vertex);
    path_len++;

    if(path_len != numOfCities){
        visited[vertex] = true;
        for (int u = 0; u < numOfCities; u++){
            if (visited[u])
                continue;

            current_cost += matrix[vertex][u];
            recursion(u);
            current_cost -= matrix[vertex][u];
        }

        visited[vertex] = false;
        path_len--;
        path.pop_back();

    }
    else if (matrix[vertex][0] <= 0){
        path_len--;
        path.pop_back();
    }
    else{
        current_cost += matrix[vertex][0];

        if (current_cost >= best_cost){
            current_cost -= matrix[vertex][0];
        }
        else{
            best_cost = current_cost;
            best_path.clear();
            for(const int& i : path)
                best_path.push_back(i);
            current_cost -= matrix[vertex][0];
        }
        path_len--;
        path.pop_back();
    }
}


/**
 * Printing function.
 */
void BF::print() {
    std::cout<<"Best path cost: " << best_cost << std::endl;

    if(best_path.empty())
        printf("\nHamiltonian path doesn't exist.");
    else {
        printf("\nShortest path:\n");
        for (const int &i: best_path)
            printf("%i -> ", i);
        std::cout << std::endl;
    }

}

