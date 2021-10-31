//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#ifndef MY_CLIB_GRAPH_H
#define MY_CLIB_GRAPH_H

#include "dictionary.h"


/**
 * Structure describing unweighted graph. Whether it is ordered or unordered, does not matter.
 */
typedef struct UnweightedGraph {
    array_size_t_ptr vertices;     /// array of pointers to vertex IDs (if they are not numerical)
    Dict* connections;
} UnweightedGraph;


/**
 * @return pointer to an unweighted graph with no vertices
 */
UnweightedGraph* new_empty_uw_graph();

/**
 * Deallocates the memory occupied by the graph. Deletes all the elements served as vertex IDs.
 */
void delete_uw_graph(UnweightedGraph* graph, void (*delete_vertex)(void*));


/**
 * Creates a new vertex with given ID and no neighbors.
 *
 * @param graph pointer to the graph
 * @param v pointer to the vertex ID
 */
void uw_graph_add_vertex(UnweightedGraph* graph, const void* v);


/**
 * Adds edge between the given vertices. If any of the vertices does not exist, nothing will be done.
 *
 * @param v1 ID of the first vertex (from where the edge will be directed)
 * @param v2 ID of the second vertex (where the edge will be directed)
 * @return 0 if any of the vertices does not exist in the graph, 1 otherwise
 */
int uw_graph_add_edge(UnweightedGraph* graph, const void* v1, const void* v2);


/**
 * @return the array of IDs of the neighbors of the given vertex
 */
array_size_t_ptr get_neighbors_uw(const UnweightedGraph* graph, const void* v);


#endif //MY_CLIB_GRAPH_H
