#include <stdio.h>
#include <malloc.h>
#include "PriorityQueue.h"
#include "Heap.h"
#include "Vertex.h"

struct Graph {
	int* edgeIndex; //entries contain pointers to edgeDestination entries (possible indices) |V| long
	int* edgeDestinations; //entries contain vertexNo's 2|E| long
	vertex* vertexList;
};

void printVertexList(vertex* list, int length) {
	int i;

	for(i = 0; i < length; i++) {
		printf("vertex[%d], gain = %d, vertexNo = %d, heapRank = %d, lock = %d, partition = %d\n"
		,i,list[i].gain,list[i].vertexNo,list[i].heapRank,list[i].locked,list[i].partition);
	}
}

int main() {
	printf("Hello, World!\n");
	int i;
	vertex* vertexList;
	int length = 5;
	vertexList = malloc( sizeof(vertex) * length);

	for( i = 0; i < length; i++) {
		vertexList[i].vertexNo = i + 1;
		vertexList[i].gain = 2 * (i + 1);
		vertexList[i].heapRank = i + 1;
		vertexList[i].locked = 0;
		vertexList[i].partition = 0;
	}
	buildHeap( vertexList, length);
	printHeap();
	printVertexList(vertexList,length);


	return 0;
}