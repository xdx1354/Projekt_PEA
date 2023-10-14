//
// Created by stani on 14.10.2023.
//

#include "BF.h"
/**
 * The function is getting graph object and performs brut force searching for optimal hamiltonian path
 * in it.
 * @param graph
 */
void BF::brut_force(Graph graph) {
    numOfCities = graph.getSize();                              // setting the value of filed

    visited = new bool[numOfCities];                       // list of currently visited cities

    // setting the lis tot false
    for(int i=0; i<numOfCities; i++){
        visited[i] = false;
    }

    path_len = 0;           // length of path (number of already visited cities)
    best_cost = INT_MAX;     // minimal cost of checked paths (currently set as maximal integer value)
    current_cost = 0;       // cost of current path

    hamiltonian_path(startingCity, graph);  // starting the search for the most optimal hamiltonian path


}
/**
 *
 * @param v : starting vertice
 */
void BF::hamiltonian_path(int v, Graph graph) {

    int u;

    path.push(v);

    if(path.getSize() < numOfCities){           // as long as there are cities that weren't visited
        visited[v] = true;                      // set current city as visited

        for(u = 0; u < numOfCities; u++){       // checking all other cities
            if(!visited[u] && v != u){          // checking if this city is not visited and (graph.v[v][u] > 0)
                current_cost += graph.v[v][u];
                hamiltonian_path(u, graph);
                current_cost -= graph.v[v][u];  // going a step back after checking all exiting routes from this vertex
            }
            visited[v] = false;                 // marking this vertex as not visited on the way back
        }
    }
    else{   // last city was reached
        current_cost += graph.v[v][startingCity]; //adding distance from last to starting city to make a loop
        if (current_cost < best_cost){
            best_cost = current_cost;
            // TODO: kopia kolejki odwiedzonych wierzcholkow
        }
        current_cost -= graph.v[v][startingCity];

    }
    path.pop();                                 // pop() from stack while exiting the recurrent
}

