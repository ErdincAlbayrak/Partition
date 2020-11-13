//
// Created by Flavius on 30.10.2017.
//
#include "Vertex.h"

#ifndef PARTITION_GRAPH_H
#define PARTITION_GRAPH_H

typedef struct Graph {
	int* edgeIndex; //entries contain pointers to edgeDestination entries (possible indices) |V| long
	int* edgeDestinations; //entries contain vertexNo's 2|E| long
	Vertex* vertexList; //entries contain pointers to vertex, |V| long
    int vertexSize;
	int edgeSize;
} Graph;

void setGraph( Graph* g);
int changePartition(int vertexNo);
void setInitialGains();
void partition();


#endif //PARTITION_GRAPH_H
