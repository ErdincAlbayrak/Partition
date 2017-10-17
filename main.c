#include <stdio.h>
#include "PriorityQueue.h"

struct Graph {
	int* vertexList; //entries contain pointers to edgeDestination entries (possible indices) |V| long
	int* edgeDestinations; //entries contain vertexNo's 2|E| long
};

struct vertex {
	int vertexNo; //[0,V]
	int heapRank; //[0,V]
	int partition; //{0,1}
	int locked; //{0,1}
};

int main() {
	printf("Hello, World!\n");
	int i;
	int j = 0;
	int k = 1;
	for(i = 0; i <= 10; i++) {
		printf( "%d, %d\n", j, j ^ 1);
		printf( "%d, %d\n", k, k ^ 1);
	}
	return 0;
}