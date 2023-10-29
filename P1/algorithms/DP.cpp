//
// Created by stani on 28.10.2023.
//

#include "DP.h"
#include "iostream"
#include "../data_structures/Stack.h"


void DP::apply()
{

    for (int i = 0; i < numOfVertices; i++)
    {
        dp[(1 << i) | 1][i] = matrix[0][i];
        history[(1 << i) | 1][i] = 0;
    }


    for (int mask = 1; mask < (1 << numOfVertices); mask++) {

        for (int v = 0; v < numOfVertices; v++) {

            if (mask & (1 << v)) {

                for (int j = 0; j < numOfVertices; j++) {

                    if (!(mask & (1 << j)) && dp[mask][v] + matrix[v][j] < dp[mask | (1 << j)][j]) {

                        history[mask | (1 << j)][j] = v;
                        dp[mask | (1 << j)][j] = dp[mask][v] + matrix[v][j];
                    }
                }
            }
        }
    }


    result = INF;
    temp = 0;

    for (int i = 0; i < numOfVertices; i++){
        temp = dp[(1 << numOfVertices) - 1][i] + matrix[i][0];
        if (temp < result){
            result = temp;
            lastVertex = i;
        }
    }
}

std::string DP::toString()
{
    std::string message = "";
    int min = 1 << 30;
    int bitMask = (1 << numOfVertices) - 1;
    int prev;
    Stack path;
    path.push_back(lastVertex);

    for (int i = numOfVertices - 2; i > 0; i--)
    {
        prev = history[bitMask][lastVertex];
        path.push_back(prev);
        bitMask = bitMask ^ (1 << lastVertex);
        lastVertex = prev;
    }

    message = "Droga: 0 ";
    message+=path.printFromBottom();
    message += "Koszt: " + std::to_string(result);

    return message;
}

int DP::getResult()
{
    return result;
}

DP::DP(Graph graph)
{
    matrix = graph.getMatrix();
    numOfVertices = graph.getSize();
    dp = new int*[1 << numOfVertices];
    history = new int*[1 << numOfVertices];
    temp, result, lastVertex = 0;

    for (int i = 0; i < (1 << numOfVertices); i++)
    {
        dp[i] = new int[numOfVertices];
        history[i] = new int[numOfVertices];
    }

    for (int i = 0; i < (1 << numOfVertices); i++)
    {
        for (int j = 0; j < numOfVertices; j++)
        {
            dp[i][j] = INF;
            history[i][j] = INF;
        }
    }
}

DP::~DP()
{
    for (int i = 0; i < (1 << numOfVertices); i++)
    {
        delete[] dp[i];
        delete[] history[i];
    }
    delete[] dp;
    delete[] history;
}