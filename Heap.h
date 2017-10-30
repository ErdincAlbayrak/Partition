//
// Created by Flavius on 17.10.2017.
//

#ifndef PARTITION_HEAP_H
#define PARTITION_HEAP_H

#include "Vertex.h"

//void buildMaxHeap(int* keys, int* vertexNumbers, int length); //deprecated
void changeKey(int heapRank, int keyChange);
int extractMax();
void buildHeap( Vertex* vertexList, int length);
void printHeap(); //testing purposes
void addNode(Vertex* vertex);
int peekMaxKey();
int peekMaxVertexNo();
int getSize();

#endif //PARTITION_HEAP_H
