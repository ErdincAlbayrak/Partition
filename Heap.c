//
// Created by Flavius on 17.10.2017.
//

#include <stdlib.h>
#include "Heap.h"

typedef struct HeapNode{
	int key;
	int vertexNo;
} HeapNode;

HeapNode* heap;
int size;

void heapify(int index) {
	int currentIndex;
	int largest;
	int stable;

	currentIndex = index;
	stable = 0;
	while (!stable) {
		//check left existence and compare
		if(2 * currentIndex <= size && heap[2 * currentIndex].key > heap[currentIndex].key) {
			largest = 2 * currentIndex;
			stable = 0;
		}
		else {
			largest = currentIndex;
			stable = 1;
		}
		//check right existence and compare
		if(2 * currentIndex + 1 <= size && heap[2 * currentIndex + 1].key > heap[largest].key) {
			largest = 2 * currentIndex + 1;
			stable = 0;
		}

		//not stable, swap and loop
		if( largest != currentIndex) {
			swapHeapNode(&heap[largest], &heap[currentIndex]);
		}
		//stable, terminate
		else {
			stable = 1;
		}

	}
}

int extractMax() {
	size = size - 1;
	swapHeapNode(&heap[0], &heap[size]);
	heapify(0);
	return heap[size].vertexNo;
}

void buildHeap(int* keys, int* vertexNumbers, int length) {
	int i;

	heap = malloc( sizeof(HeapNode) * length);
	for( i = 0; i < length; i++) {
		heap[i].key = keys[i];
		heap[i].vertexNo = vertexNumbers[i];
	}
}

void swapHeapNode(HeapNode* h1, HeapNode* h2) {
	HeapNode* swapSpace;

	*swapSpace = *h1;
	*h1 = *h2;
	*h2 = *swapSpace;
}

void changeKey(int keyChange, int* heapRank) {
	heap[*heapRank].key += keyChange;
	//change is positive, try to move up
	if(keyChange > 0) {
		while( heap[*heapRank].key > heap[(*heapRank) / 2].key) {
			swapHeapNode( &heap[*heapRank], &heap[(*heapRank) / 2]);
			*heapRank = *heapRank / 2;
		}
	}
	//change is negative, try to go down
	else {
		heapify(&heapRank);
	}
}