//
// Created by stani on 06.10.2023.
//

#ifndef P1_STACK_H
#define P1_STACK_H


#include "StackNode.h"
#include <iostream>

class Stack {
public:
    int size = 0;
    StackNode *top = nullptr;

    void push(int value);
    int pop();
    void print();
//    std::string toString();      // TODO
    int getSize();
    void clear();
    void copy(Stack s);

    void printFromBottom();
};


#endif //P1_STACK_H
