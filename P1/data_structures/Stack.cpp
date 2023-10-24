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
    void Stack::push_back(int value){
        auto* node = new StackNode(value, Stack::top);
        Stack::top = node;
        Stack::size++;
    }

    /**
     * pops the top of the Stack
     * @return: integer value of node
     */
    int Stack::pop_back() {
        auto* node = Stack::top->next;
        int val = Stack::top->value;
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

    /**
     * Clearing the structure from all data
     */
    void Stack::clear() {
        while(Stack::size>0){
            Stack::pop_back();
        }
    }


//    std::string saveBestPath(){
//        int *arr = new int[Stack::getSize()];
//        int starting_size = Stack::getSize();
//        for(int i = 1; i<=starting_size; i++){
//            arr[starting_size-i] = Stack::pop_back();
//        }
//
//    }

    void Stack::printFromBottom(){
        // moving all data to array
        int *arr = new int[Stack::getSize()];
        int starting_size = Stack::getSize();
        for(int i = 1; i<=starting_size; i++){
            arr[starting_size-i] = Stack::pop_back();
        }

        // printing the array
        for(int i = 0; i<starting_size; i++){
            std::cout<<arr[i]<<", ";
        }
    }