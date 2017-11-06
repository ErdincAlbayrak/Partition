#include <stdio.h>
#include <malloc.h>
#include "PriorityQueue.h"
#include "Vertex.h"


void partition() {
}

void printVertexList(Vertex* list, int length) {
	int i;

	for(i = 0; i < length; i++) {
		printf("vertex[%d], gain = %d, vertexNo = %d, heapRank = %d, lock = %d, partition = %d\n"
		,i,list[i].gain,list[i].vertexNo,list[i].heapRank,list[i].locked,list[i].partition);
	}
}

int main() {
	printf("Hello, World!\n");
	int i;


	//start heap test
	Vertex* vertexList;
	int length = 8;
	int maxVertexNo;
	vertexList = malloc( sizeof(Vertex) * length);

	for( i = 0; i < length; i++) {
		vertexList[i].vertexNo = i;
		vertexList[i].gain = 2 * (i + 1);
		vertexList[i].heapRank = i + 1;
		vertexList[i].locked = 0;
		vertexList[i].partition = 0;
	}
	buildHeap( vertexList, length);
	printHeap();
	printVertexList(vertexList,length);

	changeKey(6,3);
	changeKey(4,9);
	printHeap();
	printVertexList(vertexList,length);
	//extracts gain = 17
	maxVertexNo = extractMax();
	printf("extractedMax = %d, %d, %d, %d\n", maxVertexNo,
		   vertexList[maxVertexNo].vertexNo, vertexList[maxVertexNo].gain, vertexList[maxVertexNo].heapRank);
	printHeap();
	//extracts gain = 16
	maxVertexNo = extractMax();
	printf("extractedMax = %d, %d, %d, %d\n", maxVertexNo,
		   vertexList[maxVertexNo].vertexNo, vertexList[maxVertexNo].gain, vertexList[maxVertexNo].heapRank);
	printHeap();

	Vertex* addedVertex = malloc(sizeof(Vertex));
	addedVertex->gain = 20;
	addedVertex->vertexNo = 10;
	addedVertex->partition = 1;
	addedVertex->locked = 1;
	addNode(addedVertex);
	printf("addedVertex = %d, %d, %d\n",
		   addedVertex->vertexNo, addedVertex->gain, addedVertex->heapRank);
	printHeap();

	Vertex* addedVertex2 = malloc(sizeof(Vertex));
	addedVertex2->gain = 21;
	addedVertex2->vertexNo = 11;
	addedVertex2->partition = 1;
	addedVertex2->locked = 1;
	addNode(addedVertex2);
	printf("addedVertex2 = %d, %d, %d\n",
		   addedVertex2->vertexNo, addedVertex2->gain, addedVertex2->heapRank);
	printHeap();


	maxVertexNo = extractMax();
	printf("extracted Max = %d, %d, %d, %d\n", maxVertexNo,
		   addedVertex2->vertexNo, addedVertex2->gain, addedVertex2->heapRank);
	printHeap();


	//end heap test

	return 0;
}