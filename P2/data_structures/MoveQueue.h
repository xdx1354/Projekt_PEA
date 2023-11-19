//
// Created by stani on 19.11.2023.
//

#ifndef P1_MOVEQUEUE_H
#define P1_MOVEQUEUE_H


#include "Move.h"

class MoveQueue {
private:
    Move** moves;
    int maxSize;
    int front;
    int rear;
    int itemCount;

public:
    MoveQueue(int size);

    ~MoveQueue();

    void push(int city1, int city2);

    void printMoves();
};


#endif //P1_MOVEQUEUE_H
