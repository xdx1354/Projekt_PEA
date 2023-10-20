//
// Created by stani on 15.10.2023.
//

#include "DP.h"

DP::DP(){

    cost = g.getMatrix();
    n = g.getSize();




    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            dp[i][j] = -1;
            parent[i][j] = -1;
        }
    }

    int minTourCost = heldKarp(0, 1); // Start from city 0
    cout << "Minimum tour cost: " << minTourCost << endl;

    // Call the function to print the tour sequence
    printTour(0);
}


int DP::heldKarp(int current, int visited) {
    if (visited == (1 << n) - 1) {  //checking if all the cities were visited
        return cost[current][0]; // Return to the starting city
    }

    if (dp[current][visited] != -1) {   // checking if the min cost for this city has been already computed
        return dp[current][visited];    // if so, returns the computed val
    }

    int minCost = INT_MAX;              // here we start computing the cost
    int nextCity = -1;                  //

    for (int next = 0; next < n; next++) {  //looping through all possible next cities
        if (!(visited & (1 << next)) && next != current) {  // checking if city hasn't been visited and is not same city
            // calculating cost of visiting the next city from current one, and calling function for the next city
            int newCost = cost[current][next] + heldKarp(next, visited | (1 << next));
            if (newCost < minCost) { // comeback from recursion, updating the minCost and saving path
                minCost = newCost;
                nextCity = next;
            }
        }
    }

    parent[current][visited] = nextCity;    // adding the city to the path
    return dp[current][visited] = minCost;  // returning value of bes connection
}

void DP::printTour(int startCity) {
    stack<int> tour;
    int currentCity = startCity;
    int visited = 1; // We start from the starting city.

    while (true) {
        int nextCity = parent[currentCity][visited];
        tour.push(currentCity);
        visited |= (1 << currentCity);

        if (nextCity == -1) {
            break; // We have completed the tour.
        }

        currentCity = nextCity;
    }

    cout << "Optimal Tour Sequence: ";
    while (!tour.empty()) {
        cout << tour.top() << " -> ";
        tour.pop();
    }
    cout << startCity << endl;
}
