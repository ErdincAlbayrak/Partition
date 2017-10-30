//
// Created by Flavius on 27.10.2017.
//

#ifndef PARTITION_VERTEX_H
#define PARTITION_VERTEX_H

typedef struct vertex {
	int gain; //key inside heap
	int vertexNo; //[0,V]
	int heapRank; //[0,V]
	int partition; //{0,1}
	int locked; //{0,1}
} Vertex;

#endif //PARTITION_VERTEX_H
