//
// Created by stani on 06.10.2023.
//

#include "StackNode.h"

StackNode::StackNode(int value, StackNode *n) {
    StackNode::next = n;
    StackNode::value = value;

}
