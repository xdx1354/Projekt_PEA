//
// Created by stani on 06.10.2023.
//

#ifndef P1_STACK_H
#define P1_STACK_H
using namespace std;

#include "StackNode.h"
#include <iostream>

class Stack {

    // self-made stack class.

public:
    int size = 0;
    StackNode *top = nullptr;               // pointer to top item of stack

    void push_back(int value);              // method for pushing items on stack
    int pop_back();                         // method for pop
    string toString();                      // method returing Stack data as string separated with comas. Form top to bottom
    int getSize();                          // method for returning size of stack
    void clear();                           // metdod for erasing the stack
    string toStringFromBottom();            // method returning Stack data as string separated with comas. Form bottom to top
    ~Stack();

};


#endif //P1_STACK_H
