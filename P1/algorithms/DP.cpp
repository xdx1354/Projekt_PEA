//
// Created by stani on 28.10.2023.
//

#include "DP.h"
#include "iostream"
#include "../data_structures/Stack.h"


void DP::apply()
{
    for (int i = 0; i < count; i++)
    {
        memory[(1 << i) | 1][i] = matrix[0][i];
        getMemory[(1 << i) | 1][i] = 0;
    }

    for (int bitMask = 0; bitMask < 1 << count; bitMask++)
    {
        for (int v = 0; v < count; v++)
        {
            if (!(bitMask & (1 << v)))
                continue;

            for (int j = 0; j < count; j++)
            {
                if (!(bitMask & (1 << j)))
                {
                    if (memory[bitMask][v] + matrix[v][j] < memory[bitMask | (1 << j)][j])
                    {
                        getMemory[bitMask | (1 << j)][j] = v;
                        memory[bitMask | (1 << j)][j] = memory[bitMask][v] + matrix[v][j];
                    }
                }
            }
        }
    }

    result = INF;
    temp = 0;

    for (int i = 0; i < count; i++)
    {
        temp = memory[(1 << count) - 1][i] + matrix[i][0];
        if (temp < result)
        {
            result = temp;
            lastVertex = i;
        }
    }
}

std::string DP::toString()
{
    std::string message = "";
    int min = 1 << 30;
    int bitMask = (1 << count) - 1;
    int prev;
    Stack path;
    path.push_back(lastVertex);

    for (int i = count - 2; i > 0; i--)
    {
        prev = getMemory[bitMask][lastVertex];
        path.push_back(prev);
        bitMask = bitMask ^ (1 << lastVertex);
        lastVertex = prev;
    }

    message = "Droga: 0 ";
    path.print();
    std::cout << "0 \n" << "Koszt: " << std::to_string(result);

    return message;
}

int DP::getResult()
{
    return result;
}

DP::DP(Graph graph)
{
    matrix = graph.getMatrix();
    count = graph.getSize();
    memory = new int*[1 << count];
    getMemory = new int*[1 << count];
    temp, result, lastVertex = 0;

    for (int i = 0; i < (1 << count); i++)
    {
        memory[i] = new int[count];
        getMemory[i] = new int[count];
    }

    for (int i = 0; i < (1 << count); i++)
    {
        for (int j = 0; j < count; j++)
        {
            memory[i][j] = INF;
            getMemory[i][j] = INF;
        }
    }
}

DP::~DP()
{
    for (int i = 0; i < (1 << count); i++)
    {
        delete[] memory[i];
        delete[] getMemory[i];
    }
    delete[] memory;
    delete[] getMemory;
}
