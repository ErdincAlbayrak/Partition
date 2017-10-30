//
// Created by Flavius on 17.10.2017.
//

#ifndef PARTITION_PRIORITYQUEUE_H
#define PARTITION_PRIORITYQUEUE_H

#include "Vertex.h"
#include "Heap.h"

void batchEnqueue(Vertex* vertexList, int length);
void changeGain(int heapRank, int keyChange);
int dequeue(); //returns vertexNo of deuqueued Vertex
void enqueue(Vertex* vertex);
int peekVertexNo();
int peekMaxGain();
int size();

#endif //PARTITION_PRIORITYQUEUE_H
