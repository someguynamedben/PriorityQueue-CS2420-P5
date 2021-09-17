//
// Created by Benji on 4/8/2018.
//

#ifndef PRIORITYQUEUES_DYNAMICQUEUE_H
#define PRIORITYQUEUES_DYNAMICQUEUE_H

#include "ItemType.h"
#include "PQHeap.h"
#include "SkewHeap.h"

class DynamicQueue {
public:
    DynamicQueue();
    void insert(ItemType *newValue);
    ItemType* findMedian();
    void removeMedian();
    void printMedian();
private:
    ItemType* currMedian;
    int maxHeapSize;
    int minHeapSize;
    PQHeap* maxHeap;
    SkewHeap* minHeap;
};


#endif //PRIORITYQUEUES_DYNAMICQUEUE_H
