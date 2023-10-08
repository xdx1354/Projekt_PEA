//
// Created by stani on 06.10.2023.
//

#include <iostream>
#include "Stack.h"
#include "StackNode.h"

    /**
     * pushes a new value on top of the stack
     * @param value: value to be pushed on stack
     */
    void Stack::push(int value){
        auto* node = new StackNode(value, Stack::top);
        Stack::top = node;
        Stack::size++;
    }

    /**
     * pops the top of the Stack
     * @return: integer value of node
     */
    int Stack::pop() {
        auto* node = Stack::top->next;
        int val = Stack::top->value;
        delete Stack::top;
        Stack::top = node;
        Stack::size--;
        return val;
}
    /**
     * Printing a Stack structure from top to bottom
     */
    void Stack::print(){
        StackNode* node = Stack::top;
        while(node != nullptr){
            std::cout<<node->value<<" ";
            node = node->next;
        }
    }

    /**
     * return: size of the stack
     */
    int Stack::getSize() {
        return Stack::size;
    }