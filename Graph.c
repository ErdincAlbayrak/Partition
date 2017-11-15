//
// Created by Flavius on 30.10.2017.
//

#include "Graph.h"
#include "PriorityQueue.h"

Graph graph;
const double BALANCE_COEFFICIENT = 0.1;
int partitionWeigths[2];

void getAdjacencyList(int vertexNo, int* startEdge, int* endEdge) {
    *startEdge = graph.edgeIndex[vertexNo];

    if( vertexNo != graph.vertexSize)
    	*endEdge = graph.edgeIndex[vertexNo+1];
	else
		*endEdge = graph.edgeSize;
}

void setInitialGains() {
    int adjacencyStart;
    int adjacencyEnd;
    int neighborVertexNo;
    for( int i = 0; i < graph.vertexSize; i++) {
        getAdjacencyList(i,&adjacencyStart,&adjacencyEnd);

        for (int j = adjacencyStart; j < adjacencyEnd; ++j) {
            neighborVertexNo = graph.edgeDestinations[j];
            if( graph.vertexList[i].partition != graph.vertexList[neighborVertexNo].partition)
                graph.vertexList[i].gain++;
            else
                graph.vertexList[i].gain--;
        }
    }
}

void changePartition(int vertexNo) {
    int adjacencyStart;
    int adjacencyEnd;
    int neighborVertexNo;

    graph.vertexList[vertexNo].locked = 1;
    //if partition balance criterion is met, change and update gains
    if( partitionWeigths[graph.vertexList[vertexNo].partition ^ 1] + 1 <= (graph.vertexSize / 2 * (1 + BALANCE_COEFFICIENT) ) ) {
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
        //graph.vertexList[vertexNo].gain = graph.vertexList[vertexNo].gain * -1;
        graph.vertexList[vertexNo].partition = graph.vertexList[vertexNo].partition ^ 1;
    }
}


