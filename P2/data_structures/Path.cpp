//
// Created by stani on 23.12.2023.
//

#include "Path.h"
#include "Graph.h"


Path::Path(int size){
    this -> size = size;
    cost = 0;


}

int Path::calculateCost(Graph g) {
    int sum = 0;
//    std::cout<<"\n";
    for (int i = 0; i < size; i++) {
        int currentCity = citiesList[i];
        int nextCity = citiesList[(i + 1) % size];
        int val = g.getMatrix()[currentCity][nextCity];
//        std::cout<<" + "<< val;
        sum += val;
    }


//    std::cout<<" = " << sum;
//    std::cout<<"\n";
    cost = sum;
    return sum;
}



std::string Path::to_string() {

    std::string output;

    for( int i = 0; i < size; i++){
        output +=  std::to_string(citiesList[i]) + ", ";
    }

    output += std::to_string(citiesList[0]);

    return output;
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

int Path::getSize() const {
    return size;
}

void Path::setSize(int size) {
    Path::size = size;
}

Path::Path() {}

Path::~Path() {

}


