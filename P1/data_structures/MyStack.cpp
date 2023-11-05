//
// Created by stani on 05.11.2023.
//

#include "MyStack.h"

using namespace std;
MyStack::MyStack() {

}

MyStack::~MyStack() {
    if(head != nullptr){
        delete[] head;
        head = nullptr;
        size = 0;
    }
}

void MyStack::push_back(int value) {


    if(!size){
        size++;
        head = new int[1];
        head[0] = value;
    }
    else{

        int* temp = new int[size + 1]; // Create a new array with increased size
        for(int i = 0; i < size; i++) {
            temp[i] = head[i];
        }
        temp[size] = value;  // Copy the new value into temp

        delete[] head;


        head = temp;          // Update head to point to the new array
        size++;

    }
}

int MyStack::pop_back() {
    if( size < 0){                                      // if no elements return -1
        return -1;
    }
    if(size == 1){                                      // case if only one element
        int val = head[0];

        delete[] head;

        size--;
        return val;
    }
    else{
        int val = head[size-1];
        size--;
        int *temp = new int[size];

        for(int i=0; i<size; i++){                      // copying rest of elements;
            temp[i] = head[i];
        }


        head = temp;

        return val;
    }

}

int MyStack::getSize() {
    return size;
}

string MyStack::toString() {
    string stack_to_string;
    if(size == 0){
        stack_to_string = "Stack is empty";
    }
    else{
        for(int i=size-1; i>=0; i--){
            stack_to_string += to_string(head[i]) + ", ";
        }
    }
    return stack_to_string;
}


string MyStack::toStringFromBottom() {

    string stack_to_string;
    if(size == 0){
        stack_to_string = "Stack is empty";
    }
    else{
        for(int i=0; i<size; i++){
            stack_to_string += to_string(head[i]) + ", ";
        }
    }

    return stack_to_string;
}

void MyStack::clear() {
    size = 0;
    delete[] head;
    head = nullptr;

}

void MyStack::copy(MyStack *dest) {

    dest->clear();

    if(size != 0){
        for (int i = 0; i < size; i++)
        {
            dest->push_back(head[i]);
        }
    }

}
