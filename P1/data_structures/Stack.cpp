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
     * Returning a string of the Stack structure values from top to bottom
     * @return: String of values of the stack from top
     */
    std::string Stack::toString(){
        StackNode* node = Stack::top;
        std::string res = "";
        while(node != nullptr){
//            std::cout<<node->value<<" ";
            res+= std::to_string(node->value) + ", ";
            node = node->next;
        }
        return res;
    }

    /**
     * return: size of the stack
     * @return: size of the stack as int
     */
    int Stack::getSize() {
        return Stack::size;
    }

    /**
     * Clearing the structure from all data
     *
     */
    void Stack::clear() {
        while(Stack::size>0){
            Stack::pop_back();
        }
    }


    /**
     * Returning a string of the Stack structure values from bottom to top.
     * @return string of values from bottom
     */
    std::string Stack::toStringFromBottom(){
        // moving all data to array
        int *arr = new int[Stack::getSize()];
        int starting_size = Stack::getSize();
        for(int i = 1; i<=starting_size; i++){
            arr[starting_size-i] = Stack::pop_back();
        }
        // loading the array into string
        std::string res = "";
        for(int i = 0; i<starting_size; i++){
            if(i>0){
                res+=", " + std::to_string(arr[i]);
            }
            else if( i == 0){
                res+=std::to_string(arr[i]);
            }
        }

        res+=", 0";

        return res;
    }
