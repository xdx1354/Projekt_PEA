//
// Created by stani on 06.10.2023.
//

#ifndef P1_GRAPH_H
#define P1_GRAPH_H
#include <bits/stdc++.h>

/**
 * Class for representing graph as adjacency list.
 * v: two dim array of integers
 * numOfVertices: number of Vertices of graph
 *
 */
class Graph {

public:
    int **v;
    int numOfVertices;



    void loadData(std::string);
    void printGraph();
    int getSize();




};


#endif //P1_GRAPH_H
