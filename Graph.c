//
// Created by Flavius on 30.10.2017.
//

#include <malloc.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>
#include "Graph.h"
#include "PriorityQueue.h"

Graph graph;
const double BALANCE_COEFFICIENT = 0.001;
int partitionWeigths[2];

void setGraph( Graph* g) {
	graph = *g;
}

void getAdjacencyList(int vertexNo, int* startEdge, int* endEdge) {
    *startEdge = graph.edgeIndex[vertexNo];

	if( vertexNo != graph.vertexSize - 1) {
		*endEdge = graph.edgeIndex[vertexNo + 1];
	}
	else {
		*endEdge = graph.edgeSize;
	}
}

void setInitialGains() {
    int adjacencyStart;
    int adjacencyEnd;
    int neighborVertexNo;

    for( int i = 0; i < graph.vertexSize; i++) {
        getAdjacencyList(i,&adjacencyStart,&adjacencyEnd);

		graph.vertexList[i].gain = 0;
        for (int j = adjacencyStart; j < adjacencyEnd; ++j) {
            neighborVertexNo = graph.edgeDestinations[j];
			//comparison of partitions of neighbor and current
            if( graph.vertexList[i].partition != graph.vertexList[neighborVertexNo].partition)
                graph.vertexList[i].gain++;
            else
                graph.vertexList[i].gain--;
        }
    }
}

int changePartition(int vertexNo) {
    int adjacencyStart;
    int adjacencyEnd;
    int neighborVertexNo;

    graph.vertexList[vertexNo].locked = 1;
    //if partition balance criterion is met, change and update gains
	if( partitionWeigths[graph.vertexList[vertexNo].partition ^ 1] + 1
		<= (graph.vertexSize / 2 * (1 + BALANCE_COEFFICIENT) ) ) {
        //update gains of neighbors
        getAdjacencyList(vertexNo, &adjacencyStart, &adjacencyEnd);
        for (int j = adjacencyStart; j < adjacencyEnd; ++j) {
            neighborVertexNo = graph.edgeDestinations[j];
            if (!graph.vertexList[neighborVertexNo].locked) {
                if (graph.vertexList[vertexNo].partition != graph.vertexList[neighborVertexNo].partition)
                    graph.vertexList[neighborVertexNo].gain = graph.vertexList[neighborVertexNo].gain + 2;
                else
                    graph.vertexList[neighborVertexNo].gain = graph.vertexList[neighborVertexNo].gain - 2;
            }
        }
        //finally change partition
		partitionWeigths[graph.vertexList[vertexNo].partition]--;
		partitionWeigths[graph.vertexList[vertexNo].partition ^ 1]++;
        graph.vertexList[vertexNo].partition = graph.vertexList[vertexNo].partition ^ 1;
		return graph.vertexList[vertexNo].gain;
    }
	//if balance criterion is not met, no change is made so gain of move is minus infinity
	//& it will not be added to list of moves
	else {
		return INT_MIN;
	}
}

void revertPartition(int vertexNo) {
	//reduce weight of current, increment weight of other
	partitionWeigths[graph.vertexList[vertexNo].partition]--;
	partitionWeigths[graph.vertexList[vertexNo].partition ^ 1]++;
	graph.vertexList[vertexNo].partition = graph.vertexList[vertexNo].partition ^ 1;
}

int doSinglePass() {
	int currentVertexNo;
	int* prefixArray;
	int* changedVertexArray;
	int maxGain;
	int maxIndex;
	int currentGain;
	int moveNo;

	prefixArray = (int*) malloc(sizeof(int) * graph.vertexSize);
	changedVertexArray = (int*) malloc(sizeof(int) * graph.vertexSize);

	//unlock all vertices
	for (int i = 0; i < graph.vertexSize; ++i) {
		graph.vertexList[i].locked = 0;
	}

	setInitialGains();

/*	//check gains
	printf("\n");
	for (int i = 0; i < graph.vertexSize; ++i) {
		printf("vertexlist[%d].gain = %d\n", i,graph.vertexList[i].gain);
	}
	printf("\n");
	for (int i = 0; i < graph.vertexSize; ++i) {
		printf("vertexlist[%d].partition = %d\n", i,graph.vertexList[i].partition);
	}
	printf("\n");*/

	//build heap here
	buildQueue(graph.vertexList,graph.vertexSize);

	//do the tentative partition changes here
	moveNo = 0;
	for (int i = 0; i < graph.vertexSize; ++i) {
		currentVertexNo = dequeue();

/*		printf("i = %d, moveNo = %d, currentVertex = %d, its gain = %d\n",
			   i,moveNo,currentVertexNo, graph.vertexList[currentVertexNo].gain);*/

		currentGain = changePartition(currentVertexNo);
		//if move was made, add it to lists of gain and moves
		if( currentGain != INT_MIN) {
			if (moveNo == 0)
				prefixArray[moveNo] = currentGain;
			else
				prefixArray[moveNo] = currentGain + prefixArray[moveNo - 1];

			changedVertexArray[moveNo] = currentVertexNo;
			moveNo++;
		}
	}

	//delete heap here
	deleteQueue();

	//find best sequence of moves
	maxGain = INT_MIN;
	maxIndex = 0;
	for (int i = 0; i < moveNo; ++i) {
		if( prefixArray[i] > maxGain) {
			maxGain = prefixArray[i];
			maxIndex = i;
		}
	}

/*	printf("\n");
	for (int i = 0; i < moveNo; ++i) {
		printf("prefixArray[%d] = %d\n",i,prefixArray[i]);
	}
	printf("maxGain = %d, maxIndex = %d\n",maxGain,maxIndex);
	printf("\n");
	for (int i = 0; i < moveNo; ++i) {
		printf("changedArray[%d] = %d\n",i,changedVertexArray[i]);
	}*/

	//revert bad moves
	for (int i = moveNo - 1; i > maxIndex; i--) {
		revertPartition(changedVertexArray[i]);
	}

	return maxGain;
}

void partition() {
	int numberOfPasses;
	//randomize partitions
	srand((unsigned int) time(NULL));
	partitionWeigths[0] = INT_MAX;
	partitionWeigths[1] = INT_MAX;
	//arbitrary partition until balance criterion is met
	while( partitionWeigths[0] > graph.vertexSize * (1 + BALANCE_COEFFICIENT) / 2
		  || partitionWeigths[1] > graph.vertexSize * (1 + BALANCE_COEFFICIENT) / 2) {
		//reset weigths
		partitionWeigths[0] = 0;
		partitionWeigths[1] = 0;
		//randomly distribute vertices
		for (int i = 0; i < graph.vertexSize; ++i) {
			graph.vertexList[i].partition = rand() % 2;
			partitionWeigths[graph.vertexList[i].partition]++;
		}
		printf("vertexSize = %d, maxWeigth = %f\n",graph.vertexSize,graph.vertexSize * (1 + BALANCE_COEFFICIENT) / 2);
		printf("weights %d, %d\n",partitionWeigths[0],partitionWeigths[1]);
	}

/*	partitionWeigths[0] = 0;
	partitionWeigths[1] = 0;
	for (int i = 0; i < graph.vertexSize; ++i) {
		graph.vertexList[i].partition = i / 4;
		partitionWeigths[graph.vertexList[i].partition]++;
	}
	printf("weights %d, %d\n",partitionWeigths[0],partitionWeigths[1]);
	for (int i = 0; i < graph.vertexSize; ++i) {
		printf("vertexlist[%d].partition = %d\n",i,graph.vertexList[i].partition);
	}*/

	//do passes while there is gain
/*	numberOfPasses = 1;
	while( doSinglePass() > 0)
		numberOfPasses++;*/

	int maxGain = 1;
	numberOfPasses = 0;
	int timeStart,timeEnd;
	while( maxGain > 0) {
		timeStart = clock();
		maxGain = doSinglePass();
		numberOfPasses++;
		timeEnd = clock();
		printf("pass %d took %f, gain was %d\n",numberOfPasses, (timeEnd - timeStart) / (double) CLOCKS_PER_SEC, maxGain );
	}

	printf("numberOfPasses = %d\n",numberOfPasses);
}