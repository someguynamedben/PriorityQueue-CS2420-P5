//
// Created by Benji on 4/6/2018.
//

#include "SkewHeap.h"

SkewHeap::SkewHeap(){
    root = nullptr;
}
SkewHeap::SkewHeap(ItemType *itemType){
    Node node(*itemType, nullptr, nullptr);
    merge(&node, nullptr);
}

Node *SkewHeap::merge(Node *nodeOne, Node *nodeTwo){
    if(nodeOne == nullptr){
        root = nodeTwo;
        return nodeTwo;
    }
    if(nodeTwo == nullptr){
        root = nodeOne;
        return nodeOne;
    }

    if(nodeOne->element.priority > nodeTwo->element.priority){
        if(nodeOne->parent != nullptr){
            nodeOne->parent->left = nodeTwo;
        }

        nodeTwo->left = merge(nodeTwo->left, nodeOne);
        nodeTwo->left->parent = nodeTwo;
        swapChildren(nodeTwo);

        if(nodeTwo->parent == nullptr){
            root = nodeTwo;
        }

        return nodeTwo;
    }else{
        nodeOne->left = merge(nodeTwo, nodeOne->left);
        nodeOne->left->parent = nodeOne;
        swapChildren(nodeOne);

        if(nodeOne->parent == nullptr){
            root = nodeOne;
        }

        return nodeOne;
    }
}

void SkewHeap::printHeap(SkewHeap *root){
}

Node *SkewHeap::deleteMin(){
    Node *tempNode = root;

    if(tempNode->left != nullptr){
        tempNode->left->parent = nullptr;
    }
    if(tempNode->right != nullptr){
        tempNode->right->parent = nullptr;
    }

    root = merge(tempNode->right, tempNode->left);

    return tempNode;
}

void SkewHeap::swapChildren(Node *currentNode){
    Node *tempNode = currentNode->left;

    currentNode->left = currentNode->right;
    currentNode->right = tempNode;
}
