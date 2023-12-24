//
// Created by stani on 23.12.2023.
//

#ifndef P2_PATH_H
#define P2_PATH_H


#include "Graph.h"

class Path {

    int* citiesList;
    int cost;
    int size;

public:


    int *getCitiesList() const;

    void setCitiesList(int *citiesList);

    int getCost() const;

    void setCost(int cost);\

    int calculateCost(Graph g);

    ~Path();

    Path(int size);
    Path();

    std::string to_string();

    int getSize() const;

    void setSize(int size);
};


#endif //P2_PATH_H
