//
// Created by stani on 06.10.2023.
//

#ifndef P1_GRAPH_H
#define P1_GRAPH_H
#include <bits/stdc++.h>

/**
 * Class for representing graph as adjacency list.
 * v: two dim array of integers
 * numOfNodes: number of Vertices of graph
 *
 */
class Graph {

public:
    int **v;                        // matrix containing cost of traveling between cities - weights of vertices
    int numOfNodes;                 // number of cities - nodes in graph



    bool loadData(std::string);     // method for loading data with specific filename
    void printGraph();              // method for printing data
    int getSize();                  // returns number of cities
    int **getMatrix();              // returns matrix **v

};


#endif //P1_GRAPH_H
