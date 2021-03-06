//
// Created by Flavius on 17.10.2017.
//

#ifndef PARTITION_PRIORITYQUEUE_H
#define PARTITION_PRIORITYQUEUE_H

#include "Vertex.h"
#include "Heap.h"

void buildQueue(Vertex* vertexList, int length);
void deleteQueue();
void changeGain(int heapRank, int keyChange);
int dequeue(); //returns vertexNo of deuqueued Vertex
void enqueue(Vertex* vertex);
int peekVertexNo();
int peekMaxGain();
int getQueueSize();

#endif //PARTITION_PRIORITYQUEUE_H
