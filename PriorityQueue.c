//
// Created by Flavius on 17.10.2017.
//

#include "PriorityQueue.h"

void buildQueue(Vertex* vertexList, int length) {
	buildHeap(vertexList, length);
}

void deleteQueue() {
	deleteHeap();
}

void changeGain(int heapRank, int keyChange) {
	changeKey(heapRank, keyChange);
}

int dequeue() {
	return extractMax();
}

void enqueue(Vertex* vertex) {
	addNode(vertex);
}

int peekVertexNo() {
	return peekMaxVertexNo();
}
int peekMaxGain() {
	return peekMaxKey();
}

int getQueueSize() {
	return getSize();
}