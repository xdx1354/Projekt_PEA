//
// Created by stani on 15.10.2023.
//

#include "DP.h"
#include "../data_structures/Graph.h"

using namespace std;

int DP::apply() {

    // creating Dynamic Programing Array dp and filling it with INF
//    for(int i = 0; i < (1 << numOfCities); i++){
//        for(int j = 0; j < numOfCities; j++){
//            dp[i][j] = INT_MAX;
//            cout<<dp[i][j]<<"  ";
//        }
//        cout<<"\n";
//    }

    vector<vector<int>> dp(1 << numOfCities, vector<int>(numOfCities, INT_MAX));



    //Setting first city as visited
    for(int i = 0; i< numOfCities; i++){
        dp[1 << i][i] = 0;
    }


    // dynamic calculations
    for(int mask = 1; mask < (1 <<numOfCities); mask++){

        for(int u = 0; u < numOfCities; u++){
//            cout<<"HALO";
            if ((mask & (1 << u)) != 0) {
                for (int v = 0; v < numOfCities; v++) {
                    if (u != v && (mask & (1 << v)) != 0) {
                        dp[mask][u] = min(dp[mask][u], dp[mask ^ (1 << u)][v] + matrix[v][u]);
//                        cout<<"mask: " << mask <<" u: " << u << dp[mask][u];
                    }
                }
            }
        }
    }

    // calculating official result
    int mask = (1 << numOfCities) - 1;
    int minTour = INT_MAX;

    for (int u = 0; u < numOfCities; u++) {
        if (u != 0) {
            minTour = min(minTour, dp[mask][u] + matrix[u][0]);
        }
    }


    // TODO: should also print the Path!!
    return minTour;

}





DP::DP(Graph graph) {


    matrix = graph.getMatrix();
    numOfCities = graph.getSize();

}