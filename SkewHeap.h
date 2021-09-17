//
// Created by Benji on 4/6/2018.
//

#ifndef PRIORITYQUEUES_SKEWHEAP_H
#define PRIORITYQUEUES_SKEWHEAP_H

#include "ItemType.h"
#include "Node.h"
#include <utility>

class SkewHeap {
public:
    SkewHeap();
    SkewHeap(ItemType* itemType);
    Node* merge(Node* nodeOne, Node* nodeTwo);
    void printHeap(SkewHeap* root);
    Node* deleteMin();
    Node* root;

private:
    void swapChildren(Node* currentNode);
};


#endif //PRIORITYQUEUES_SKEWHEAP_H
