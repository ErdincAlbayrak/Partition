//
// Created by Flavius on 17.10.2017.
//

#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"

Vertex** heap;
int size;
int maxSize;

int getSize() {
	return size;
}

void swapVertex(Vertex** h1, Vertex** h2) {
	Vertex* swapSpace;
	int rank1;

	//exchange heapRanks
	rank1 = (*h1)->heapRank;
	(*h1)->heapRank = (*h2)->heapRank;
	(*h2)->heapRank = rank1;

	//exchange pointer references
	swapSpace = *h1;
	*h1 = *h2;
	*h2 = swapSpace;
}

void heapify(int index) {
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
}

int extractMax() {
	swapVertex(&heap[1], &heap[size]);
	size = size - 1;
	heapify(1);
	return heap[size + 1]->vertexNo;
}

int peekMaxKey() {
	return heap[1]->gain;
}

int peekMaxVertexNo() {
	return heap[1]->vertexNo;
}

void buildHeap( Vertex* vertexList, int length) {
	int i;
	size = length;
	maxSize = length;
	heap = malloc( (size + 1) * sizeof(Vertex*)); //size + 1 because index 0 will be empty.

	//heap[i + 1] because we want heap to start with index 1
	for( i = 0; i < length; i++) {
		heap[i + 1] = vertexList + i;
		heap[i + 1]->heapRank = i + 1;
	}

	for ( i = size / 2; i >= 1; i--) {
		heapify(i);
	}
}

void changeKey(int heapRank, int keyChange) {
	//entry conditions
	if( heapRank > 0 && heapRank <= size && keyChange != 0) {
		heap[heapRank]->gain += keyChange;
		//change is positive, try to move up
		if(keyChange > 0) {
			while( heap[heapRank]->gain > heap[(heapRank) / 2]->gain && heapRank > 1) {
				swapVertex( &heap[heapRank], &heap[(heapRank) / 2]);
				heapRank = heapRank / 2;
			}
		}
		//change is negative, try to go down
		else {
			heapify(heapRank);
		}
	}
}

void printHeap() {
	printf( "heap[0].gain = %d(should be garbage)\n", heap[0]->gain);
	for (int i = 1; i <= size ; i++) {
		printf("heap[%d].gain = %d\n", i, heap[i]->gain);
	}
}

void addNode(Vertex* vertex) {
	int newRank;
	//need to create new set of pointers and
	if( size == maxSize) {
		printf("extending heap\n");
		maxSize  = maxSize + 1;
		Vertex** newHeap = malloc(sizeof(Vertex*) * (maxSize + 1) );

		for(int i = 1; i <= size; i++) {
			newHeap[i] = heap[i];
		}
		free(heap);
		heap = newHeap;
	}

	//addition of new element
	size = size + 1;
	heap[size] = vertex;
	heap[size]->heapRank = size;
	//new value should be heapified upwards
	newRank = size;
	while( heap[newRank]->gain > heap[(newRank) / 2]->gain && newRank > 1) {
		swapVertex( &heap[newRank], &heap[(newRank) / 2]);
		newRank = newRank / 2;
	}
}

void deleteHeap() {
	free(heap);
	size = 0;
	maxSize = 0;
}