#include "PQHeap.h"
#include <time.h>
#include "SkewHeap.h"
#include "DynamicQueue.h"

//Insert limit elements of the file fin into heap.
void insertNext(PQ & pq, std::ifstream & fin, int limit = 0)
{	if (limit == 0)
		limit = std::numeric_limits<int>::max();
	std::string word;
	int ct;
	for (int i = 0; i <= limit && !fin.eof(); i++)
	{
		fin >> word >> ct;
		//std::cout << "inserting " << word << " " << ct << std::endl;
		ItemType item(word, ct);
		pq.insert(item);
	}
}

int main()
{   clock_t start = clock();
	int const DELETE_CT = 20;
	int const PRINTSIZE = 30;
	int const HOWMANY = 100;

	PQHeap pqMax("MaxHeap",6000);

	std::ifstream fin;
	fin.open("Prog5In.txt");
	assert(fin);

    std::cout << "Testing Priority Queue:" << std::endl << std::endl;

	for (int i = 0; i < 60; i++)
	{
		insertNext(pqMax, fin, HOWMANY);
	}

    for(int i = 0; i < 60; i++){
        std::cout << pqMax.deleteMax().toString() << std::endl;
    }

	clock_t time = clock() - start;
	std::cout << "Elapsed time = " << ((float) time) / CLOCKS_PER_SEC << std::endl;

    std::cout << std::endl << "Testing Skew Heap:" << std::endl << std::endl;

    fin.clear();
    fin.seekg(0, fin.beg);

    SkewHeap* skewHeap = new SkewHeap();

    std::string word;
    int ct;
    for (int i = 0; i <= HOWMANY && !fin.eof(); i++)
    {
        fin >> word >> ct;
        //std::cout << "inserting " << word << " " << ct << std::endl;
        ItemType item(word, ct);
        Node *node = new Node(item, nullptr, nullptr);
        skewHeap->merge(skewHeap->root, node);
    }

    for(int i = 0; i < 60; i++){
        std::cout << skewHeap->deleteMin()->toString() << std::endl;
    }

    std::cout << std::endl << "Testing Dynamic Median Queue:" << std::endl << std::endl;

    fin.clear();
    fin.seekg(0, fin.beg);

    DynamicQueue* dynamicQueue = new DynamicQueue();
    int frequencyCount = 0;

    for (int i = 0; i < 5860; i++)
    {
        fin >> word >> ct;
        //std::cout << "inserting " << word << " " << ct << std::endl;
        dynamicQueue->insert(new ItemType(word, ct));
        frequencyCount++;

        if(frequencyCount >= 100){
            std::cout << dynamicQueue->findMedian()->toString() << std::endl;
            frequencyCount = 0;
        }
    }

	//std::cin.ignore();
}


