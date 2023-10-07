//
// Created by stani on 06.10.2023.
//

#ifndef P1_STACK_H
#define P1_STACK_H


#include "StackNode.h"

class Stack {
public:
    int size;
    StackNode *top = nullptr;

    void push(int value);
    int pop();
    void print();

};


#endif //P1_STACK_H
