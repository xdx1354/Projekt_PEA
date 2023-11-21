//
// Created by stani on 19.11.2023.
//

#include "MoveQueue.h"

#include <iostream>

MoveQueue::MoveQueue(int size) : maxSize(size), front(0), rear(-1), itemCount(0) {
    moves = new Move*[size];
    for (int i = 0; i < size; ++i) {
        moves[i] = nullptr;
    }
}

MoveQueue::~MoveQueue() {
    for (int i = 0; i < maxSize; ++i) {
        delete moves[i];
    }
    delete[] moves;
}

void MoveQueue::push(int city1, int city2) {
    if (itemCount == maxSize) {
        delete moves[front];
        front = (front + 1) % maxSize;
        itemCount--;
    }

    rear = (rear + 1) % maxSize;
    moves[rear] = new Move(city1, city2);
    itemCount++;
}

void MoveQueue::printMoves() {
    int current = front;
    std::cout << "Curently restricted steps: ";
    for (int i = 0; i < itemCount; ++i) {
        std::cout << "(" << moves[current]->city1 << " <-> " << moves[current]->city2 << ") ";
        current = (current + 1) % maxSize;
    }
    std::cout << std::endl;
}

bool MoveQueue::findMove(int c1, int c2) {

    for(int i=0; i < maxSize; i++){
        // checking if move (c1 <-> c2) or (c2 <-> c1) is restricted
        if((moves[i]->city1 == c1 and moves[i] -> city2 == c2) or (moves[i]->city1 == c2 and moves[i] -> city2 == c1))
            return true;
    }
    return false;
}
