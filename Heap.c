//
// Created by Flavius on 17.10.2017.
//

#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"
#include "Vertex.h"

vertex** heap;
int size;

void swapVertex(vertex** h1, vertex** h2) {
	vertex* swapSpace;
	int rank1;

	//heap[largest]->heapRank = currentIndex;
	//heap[currentIndex]->heapRank = largest;
	//change heapRanks
	rank1 = (*h1)->heapRank;
	(*h1)->heapRank = (*h1)->heapRank;
	(*h2)->heapRank = rank1;

	//exchange pointer references
	swapSpace = *h1;
	*h1 = *h2;
	*h2 = swapSpace;
}

int heapify(int index) {
	int currentIndex;
	int largest;
	int stable;

	currentIndex = index;
	stable = 0;
	while ( stable != 1) {
		//check left existence and compare
		if(2 * currentIndex <= size && heap[2 * currentIndex]->gain > heap[currentIndex]->gain) {
			largest = 2 * currentIndex;
			stable = 0;
		}
		else {
			largest = currentIndex;
			stable = 1;
		}

		//check right existence and compare
		if(2 * currentIndex + 1 <= size && heap[2 * currentIndex + 1]->gain > heap[largest]->gain) {
			largest = 2 * currentIndex + 1;
			stable = 0;
		}

		//not stable, swap and loop
		if( largest != currentIndex) {
			swapVertex(&heap[largest], &heap[currentIndex]);
			currentIndex = largest;
		}
		//stable, terminate
		else {
			stable = 1;
		}
	}
	return currentIndex;
}

int extractMax() {
	size = size - 1;
	swapVertex(&heap[1], &heap[size]);
	heapify(1);
	return heap[size]->vertexNo;
}

void buildHeap( vertex* vertexList, int length) {
	int i;
	size = length;
	heap = malloc( (size + 1) * sizeof(vertex*)); //size + 1 because index 0 will be empty.

	//heap[i + 1] because we want heap to start with index 1
	for( i = 0; i < length; i++) {
		heap[i + 1] = vertexList + i;
		heap[i + 1]->heapRank = i + 1;
	}

	for ( i = size / 2; i >= 1; i--) {
		heapify(i);
	}
}

void changeKey(int keyChange, int* heapRank) {
	heap[*heapRank]->gain += keyChange;
	//change is positive, try to move up
	if(keyChange > 0) {
		while( heap[*heapRank]->gain > heap[(*heapRank) / 2]->gain && *heapRank > 1) {
			swapVertex( &heap[*heapRank], &heap[(*heapRank) / 2]);
			*heapRank = *heapRank / 2;
		}
	}
	//change is negative, try to go down
	else {
		*heapRank = heapify(*heapRank);
	}
}

void printHeap() {
	printf( "%d, heap[0](should be garbage)\n", heap[0]->gain);
	for (int i = 1; i <= size ; i++) {
		printf("heap[%d].gain = %d\n", i, heap[i]->gain);
	}
}