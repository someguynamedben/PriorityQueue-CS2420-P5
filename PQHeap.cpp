#include "PQHeap.h"

//Create a heap with maximum size "physicalSize" 
PQHeap::PQHeap(std::string name, int physicalSize )
{  
	this->name = name;
	size = 0;
	heap = new ItemType[physicalSize];
	this->physicalSize = physicalSize;
}



// insert element and re-heapify
void PQHeap::insert(ItemType &newVal)
{  
	int curr = size;
	assert(size < physicalSize);
	int parent = (curr - 1) / KIDS; // round down
	while( curr > 0 && newVal.priority > heap[parent].priority ) {
		heap[curr] = heap[parent];
		curr = parent;
		parent = (curr - 1) / KIDS;
	}

	heap[curr] = newVal;
	size++;
}


// Delete maximum value, re-heapify, and return max element
ItemType PQHeap::deleteMax()
{  	
	if (size == 0) {
        return ItemType("error", -1);
    }

	ItemType toReturn = heap[0];
	size--;
	ItemType currVal = heap[size];
	int curr = 0;
	int left = 1;
	int leftMid = left + 1;
    int rightMid = leftMid + 1;
    int right = rightMid + 1;

	while( ( left < size && currVal.priority < heap[left].priority) ||
            ( leftMid < size && currVal.priority < heap[leftMid].priority) ||
            ( rightMid < size && currVal.priority < heap[rightMid].priority) ||
            ( right < size && currVal.priority < heap[right].priority )){
        int bestChild = left;

        if( leftMid < size && heap[leftMid].priority > heap[left].priority ){
            bestChild = leftMid;
        }else if( rightMid < size && heap[rightMid].priority > heap[leftMid].priority ){
            bestChild = rightMid;
        }else if( right < size && heap[right].priority > heap[rightMid].priority ){
            bestChild = right;
        }

        heap[curr] = heap[bestChild];
        curr = bestChild;
        left = KIDS * bestChild + 1;
        leftMid = left + 1;
        rightMid = leftMid + 1;
        right = leftMid + 1;
	} // endwhile

	heap[curr] = currVal;

	return toReturn;
}


// merge second into current  heap
void PQHeap::merge(PQ * second)
{  
	for (int i=0; i < second->getSize(); i++) {
        insert(dynamic_cast<PQHeap *>(second)->heap[i]);
    }

	second->makeEmpty();
}

// Convert first "size: elements of PQ to a string.
std::string PQHeap::toString(int maxSize) const
{   const int PERLINE = 5;
	std::stringstream out;
	out <<  name << "  current size=" << size;

	if (maxSize > size) {
        maxSize = size;
    }

	for (int i = 0; i < maxSize; i++){
		if (i % PERLINE == 0) out << std::endl;
		out << heap[i].toString() << "\t";
	}

	out << std::endl;

	return out.str();
}