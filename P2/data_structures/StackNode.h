//
// Created by stani on 06.10.2023.
//

#ifndef P1_STACKNODE_H
#define P1_STACKNODE_H


class StackNode {
public:
    int value;                              // integer value of element
    StackNode* next;                       // single element of stack

    StackNode(int value, StackNode *n);    // constructor

};


#endif //P1_STACKNODE_H
