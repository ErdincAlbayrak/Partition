#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "PriorityQueue.h"
#include "Vertex.h"
#include "Graph.h"


void printVertexList(Vertex* list, int length) {
	int i;

	for(i = 0; i < length; i++) {
		printf("vertex[%d], gain = %d, vertexNo = %d, heapRank = %d, lock = %d, partition = %d\n"
		,i,list[i].gain,list[i].vertexNo,list[i].heapRank,list[i].locked,list[i].partition);
	}
}

Graph* createGraph(char* fileAddress, int vertexNo, int edgeNo) {
	FILE* file;
	Vertex* vertexList;
	int* edgeIndex;
	int* edgeDestinations;
	char stringBuffer[32];
	char numberBuffer[8];
	char currentChar;
	int lastSource;
	int c;
	int k;
	int i;
	int vertexCollector;
	int incorrectName;
	int correctName;

	file = fopen(fileAddress,"r");
	vertexList = malloc( sizeof(Vertex) * vertexNo);
	edgeIndex = malloc( sizeof(int) * vertexNo);
	edgeDestinations = malloc( sizeof(int) * edgeNo);

	vertexCollector = 0;
	i = 0;
	fgets(stringBuffer, 32, file);
	do {
		//take source vertex
		c = 0;
		currentChar = stringBuffer[c];
		while ( currentChar != '\t' && currentChar != ' ') {
			numberBuffer[c] = stringBuffer[c];
			c++;
			currentChar = stringBuffer[c];
		}
		numberBuffer[c] = '\0';


		//if this source is same as last source, do not increment edgeIndex array
		//printf("lastSource = %d, currentNumber = %d, i=%d\n\n", lastSource,atoi(numberBuffer),i );
		if ( vertexCollector == 0) {
			edgeIndex[vertexCollector] = i;
			vertexList[vertexCollector].vertexName = atoi(numberBuffer);
			vertexList[vertexCollector].vertexNo = vertexCollector;
			vertexCollector++;
			lastSource = atoi(numberBuffer);
		}
		else if ( lastSource != atoi(numberBuffer)) {
			edgeIndex[vertexCollector] = i;
			vertexList[vertexCollector].vertexName = atoi(numberBuffer);
			vertexList[vertexCollector].vertexNo = vertexCollector;
			vertexCollector++;
			lastSource = atoi(numberBuffer);
		}
		//printf("reahced \n");

		//take destination vertex
		k = 0;
		c++;
		currentChar = stringBuffer[c];
		while (currentChar != '\n' && currentChar != ' ' && currentChar != '\r') {
			numberBuffer[k] = stringBuffer[c];
			c++;
			currentChar = stringBuffer[c];
			k++;
		}
		numberBuffer[k] = '\0';
		edgeDestinations[i] = atoi(numberBuffer);
		i++;

	} while(  fgets(stringBuffer, 32, file) != NULL );

	//fix edgeDestinations from being vertexName to vertexNo
	for ( i = 0; i < vertexNo; ++i) {
		incorrectName = vertexList[i].vertexName;
		correctName = vertexList[i].vertexNo;
		for (int j = 0; j < edgeNo; ++j) {
			if(edgeDestinations[j] == incorrectName)
				edgeDestinations[j] = correctName;
		}
	}


	//malloc graph and set its fields
	Graph* g = malloc(sizeof(Graph) * 1);
	g->edgeDestinations = edgeDestinations;
	g->edgeIndex = edgeIndex;
	g->vertexList = vertexList;
	g->edgeSize = edgeNo;
	g->vertexSize = vertexNo;
	return g;
}

int main() {
	printf("Hello, World!\n");
	int i;
	Graph* graph;
	graph = createGraph("CA-GrQc.txt",5242, 28980);

/*	printf("vertexsize = %d, edgeSize = %d\n\n",graph->vertexSize,graph->edgeSize);
	for( i = 0; i < graph->vertexSize; i++) {
		printf("vertexList[%d].vertexName = %d\n",i,graph->vertexList[i].vertexName );
		printf("vertexlist[%d].vertexNo = %d\n",i,graph->vertexList[i].vertexNo );
		printf("graph.edgeIndex[%d] = %d\n\n",i, graph->edgeIndex[i]);
	}*/

	setGraph(graph);
	printf("set the graph\n");
	partition();

/*
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
*/

	return 0;
}