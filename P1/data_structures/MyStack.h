//
// Created by stani on 05.11.2023.
//

#ifndef P1_MYSTACK_H
#define P1_MYSTACK_H
#include <iostream>


class MyStack {
public:
    int size = 0;
    int *head = nullptr;

    void push_back(int value);
    int pop_back();
    std::string toString();
    int getSize();
    void clear();
    std::string toStringFromBottom();
    ~MyStack();
    MyStack();
    void copy(MyStack *dest);


};


#endif //P1_MYSTACK_H
