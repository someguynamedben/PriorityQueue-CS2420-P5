//
// Created by Benji on 4/8/2018.
//

#include "DynamicQueue.h"

DynamicQueue::DynamicQueue(){
    maxHeap = new PQHeap("MaxHeap2", 6000);
    minHeap = new SkewHeap();
    currMedian = new ItemType("", -1);
    minHeapSize = 0;
    maxHeapSize = 0;
}

void DynamicQueue::insert(ItemType *newValue){
    if(currMedian->priority == -1){
        currMedian = newValue;
    }else if(newValue->priority > currMedian->priority){
        minHeap->merge(minHeap->root, new Node(*newValue, nullptr, nullptr));
        minHeapSize++;
    }else if(newValue->priority <= currMedian->priority){
        maxHeap->insert(*newValue);
        maxHeapSize++;
    }else{
        std::cout << "value wasn't inserted" << std::endl;
    }

    if(minHeapSize - 1 > maxHeapSize){
        maxHeap->insert(*currMedian);
        maxHeapSize++;
        ItemType temp = minHeap->deleteMin()->element;
        currMedian = new ItemType(temp.word, temp.priority);
        minHeapSize--;
    }else if(maxHeapSize - 1 > minHeapSize){
        minHeap->merge(minHeap->root, new Node(*currMedian, nullptr, nullptr));
        minHeapSize++;
        ItemType temp = maxHeap->deleteMax();
        currMedian = new ItemType(temp.word, temp.priority);
        maxHeapSize--;
    }
}

ItemType* DynamicQueue::findMedian(){
    return currMedian;
}

void DynamicQueue::removeMedian(){
    if(maxHeapSize > minHeapSize){
        ItemType temp = maxHeap->deleteMax();
        currMedian = new ItemType(temp.word, temp.priority);
        maxHeapSize--;
    }else{
        currMedian = &minHeap->deleteMin()->element;
        minHeapSize--;
    }
}

void DynamicQueue::printMedian(){
    currMedian->toString();
}
