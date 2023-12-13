//
// Created by stani on 19.11.2023.
//

#ifndef P1_MOVEQUEUE_H
#define P1_MOVEQUEUE_H


#include "Move.h"
/**
 * Cyclic Queue
 */
class MoveQueue {
private:
    Move** moves;                   // 2-dim array storing moves
    int maxSize;                    // max size - param l - evaluated in paper
    int front;                      // id of currently first cell
    int rear;                       // id of currently last cell
    int itemCount;                  // field keeping track of number of items

public:
    MoveQueue(int size);                // constructor
    ~MoveQueue();                       // destructor
    void push(int city1, int city2);    // push move as a pair of cities
    void printMoves();                  // printing Queue
    void clear();                       // erasing
    bool findMove(int c1, int c2);      //
};


#endif //P1_MOVEQUEUE_H
