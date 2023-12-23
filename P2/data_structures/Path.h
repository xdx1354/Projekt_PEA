//
// Created by stani on 23.12.2023.
//

#ifndef P2_PATH_H
#define P2_PATH_H


class Path {

    int* citiesList;
    int cost;
    int size;

public:


    int *getCitiesList() const;

    void setCitiesList(int *citiesList);

    int getCost() const;

    void setCost(int cost);\

    int calculateCost();

    ~Path();

    Path(int size);
};


#endif //P2_PATH_H
