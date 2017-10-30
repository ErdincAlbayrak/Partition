//
// Created by Flavius on 17.10.2017.
//

#ifndef PARTITION_HEAP_H
#define PARTITION_HEAP_H

#include "Vertex.h"

void buildMaxHeap(int* keys, int* vertexNumbers, int length);
void changeKey(int keyChange, int* heapRank);
int extractMax();
void buildHeap( vertex* vertexList, int length);
void printHeap(); //testing purposes

#endif //PARTITION_HEAP_H
