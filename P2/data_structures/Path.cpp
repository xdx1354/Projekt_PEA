//
// Created by stani on 23.12.2023.
//

#include "Path.h"


Path::Path(int size){
    this -> size = size;
    cost = 0;


}

int Path::calculateCost() {

    int sum;

    for(int i = 0; i < size; i++){
        sum += citiesList[i];
    }
    cost = sum;

    return sum;
}

int *Path::getCitiesList() const {
    return citiesList;
}

void Path::setCitiesList(int *citiesList) {
    Path::citiesList = citiesList;
}

int Path::getCost() const {
    return cost;
}

void Path::setCost(int cost) {
    Path::cost = cost;
}

