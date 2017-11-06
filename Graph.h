//
// Created by Flavius on 30.10.2017.
//
#include "Vertex.h"

#ifndef PARTITION_GRAPH_H
#define PARTITION_GRAPH_H

typedef struct Graph {
	int* edgeIndex; //entries contain pointers to edgeDestination entries (possible indices) |V| long
	int* edgeDestinations; //entries contain vertexNo's 2|E| long
	Vertex* vertexList;
    int size;
} Graph;

void buildGraphFromFile();
void changePartition(int vertexNo);
void setInitialGains();
void changePartition(int vertexNo);


#endif //PARTITION_GRAPH_H
