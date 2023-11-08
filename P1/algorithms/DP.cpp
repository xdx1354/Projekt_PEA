//
// Created by stani on 28.10.2023.
//

#include "DP.h"
#include "iostream"
#include "../data_structures/Stack.h"

/**
 * Applies the Dynamic Programing algorithm on the graph.
 */
void DP::apply()
{

    for (int i = 0; i < numOfCities; i++)
    {
        dp[(1 << i) | 1][i] = matrix[0][i];             // asigning value of first edge for each binnary mask containg only i-city visited
        history[(1 << i) | 1][i] = 0;                   // marking 0 as a previous city for city i
    }


    for (int mask = 1; mask < (1 << numOfCities); mask++) {   // iterating through all possible sets of visited cites

        for (int v = 0; v < numOfCities; v++) {               // iterating through all cities 0 - numOfCities

            if (mask & (1 << v)) {                              // checks if current city v is marked as visited in the mask
                                                                // if so
                for (int j = 0; j < numOfCities; j++) {         // iterate again thorough all of cities


                    // checking if j-city is not a part of mask - current set of visited cities AND
                    // cost of traveling for this mask with v as last city  + cost of traveling from v-city to j-city
                    // is lower than cost of traveling for mask but with j-city as the last one

                    //basically it tries to add j at the end of the set and checks weather there is cheaper option for traveling thorough this set and ending in j-city TODO: verify
                    if (!(mask & (1 << j)) && dp[mask][v] + matrix[v][j] < dp[mask | (1 << j)][j]) {

                        history[mask | (1 << j)][j] = v;                                            // setting v as previous city
                        dp[mask | (1 << j)][j] = dp[mask][v] + matrix[v][j];                        // saving cost of the travel
                    }
                }
            }
        }
    }


    result = INF;
    temp = 0;

    for (int i = 0; i < numOfCities; i++){
        temp = dp[(1 << numOfCities) - 1][i] + matrix[i][0];    // calcuating cost of each hamiltionan path by adding the last vertex
        if (temp < result){                                     // in the same time keeping track of currently the cheapest one
            result = temp;
            lastVertex = i;                                     // and the last vertex on his way in order to be able to retrieve the whole path
        }
    }
}

/**
 * Returns string containing answer. Value of path + the real path
 * @return: string containing answer.
 */
std::string DP::resultToString()
{
    std::string message = "";
    int min = 1 << 30;
    int bitMask = (1 << numOfCities) - 1;
    int prev;
    Stack path;
    path.push_back(lastVertex);

    for (int i = numOfCities - 2; i > 0; i--)                   // going back from last vertex to the beginning of the path
    {
        prev = history[bitMask][lastVertex];
        path.push_back(prev);                              // storing the data on the stack
        bitMask = bitMask ^ (1 << lastVertex);
        lastVertex = prev;
    }

    message = "Best path cost: "  + std::to_string(result);
    message += "\nShortest path:\n0, ";
    message += path.toString() + "0\n\n";

    return message;
}

/**
 * Printing the answer
 */
void DP::printResult()
{
    std::cout<<resultToString();
}

/**
 * Constructor for the class. Prepares data for DP algorithm. Creates dynamic tables and initializes their data
 * @param graph
 */
DP::DP(Graph graph)
{
    matrix = graph.getMatrix();                     // gets matrix of graph
    numOfCities = graph.getSize();                  // gets the size of graph
    dp = new int*[1 << numOfCities];                // allocates the dynamic programming array for data
    history = new int*[1 << numOfCities];           // allocates historic table for retrieving the path
    temp, result, lastVertex = 0;                   // initializes helping variables

    for (int i = 0; i < (1 << numOfCities); i++)    // allocates space for 2nd dimension of arrays
    {
        dp[i] = new int[numOfCities];
        history[i] = new int[numOfCities];
    }

    for (int i = 0; i < (1 << numOfCities); i++)    // initializes starting values
    {
        for (int j = 0; j < numOfCities; j++)
        {
            dp[i][j] = INF;
            history[i][j] = INF;
        }
    }
}


void DP::run(){
    apply();
    printResult();
}

DP::~DP()
{
    for (int i = 0; i < (1 << numOfCities); i++)
    {
        delete[] dp[i];
        delete[] history[i];
    }
    delete[] dp;
    delete[] history;
}
