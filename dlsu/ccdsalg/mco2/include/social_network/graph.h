/*
 * Social Network processes a graph for its details and traversal sequences.
 * Copyright (C) 2025  Raphael Panaligan  Jek Degullado
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file graph.h
 * @brief The public APIs of the graph implementation and its helper functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifndef SOCIAL_NETWORK_GRAPH_H_
#define SOCIAL_NETWORK_GRAPH_H_

#include <stdbool.h>
#include <stddef.h>

/** @brief The maximum number of characters a vertex's label can have. */
#define MAX_VERTEX_LABEL_LENGTH 8

/** @brief The maximum number of vertices a graph can contain. */
#define MAX_GRAPH_ORDER 20

/** @brief A string-labeled vertex in a graph. */
typedef char Vertex[MAX_VERTEX_LABEL_LENGTH + 1];

/**
 * @brief A collection implementing the [adjacency list graph
 * structure](https://www.geeksforgeeks.org/dsa/adjacency-list-meaning-definition-in-dsa/) using arrays.
 */
typedef struct Graph {
  /**
   * @brief The number of vertices the graph contains.
   * @private
   */
  size_t order;
  /**
   * @brief The vertices mapped to their adjacent vertices.
   * @details This contains arrays of vertices, where the first vertex is the key, and the rest are the adjacent
   * vertices or values.
   * @private
   */
  Vertex adjacencies_by_vertex[MAX_GRAPH_ORDER][MAX_GRAPH_ORDER];
  /**
   * @brief The number of vertex adjacency arrays the graph contains.
   * @private
   */
  size_t adjacencies_length;
} Graph;

/**
 * @brief Initializes a graph's order, and vertex adjacency arrays to their default values.
 * @details This sets the graph's order, and the adjacency array vertex label elements to empty strings.
 * @relates Graph
 * @param[in,out] graph The graph to initialize.
 * @param graph_order The number of vertices the graph should contain.
 * @pre The `graph_order` doesn't exceed `MAX_GRAPH_ORDER`.
 */
void initialize_graph(Graph* const graph, size_t graph_order);

/**
 * @brief Gets the index of the adjacency array of a vertex from a graph.
 * @relates Graph
 * @param[in] graph The graph to get from.
 * @param[in] vertex The vertex to get the index of.
 * @return The index of the vertex' adjacency array, or `MAX_GRAPH_ORDER` if the graph doesn't contain the
 * vertex.
 */
size_t get_vertex_index(const Graph* const graph, const Vertex vertex);

/**
 * @brief Checks if a graph contains a vertex.
 * @relates Graph
 * @param[in] graph The graph to check.
 * @param[in] vertex The vertex to check for.
 * @return Whether the graph contains the vertex.
 */
bool has_vertex(const Graph* const graph, const Vertex vertex);

/**
 * @brief Adds an adjacency between a pair of vertices to a graph.
 * @details This adds the adjacent vertex to the array of the key vertex. If the array doesn't exist, this creates the
 * array before adding the adjacent vertex. If an adjacent vertex is not supplied, then this will still create the array
 * for the key vertex if it doesn't exist.
 * @relates Graph
 * @param[in,out] graph The graph to add to.
 * @param[in] key_vertex The key vertex of the adjacency.
 * @param[in] adjacent_vertex The vertex adjacent to the key vertex.
 * @pre The graph's adjacencies length does not exceed its order, and the number of vertices will not exceed
 * `MAX_GRAPH_ORDER`.
 */
void add_adjacency(Graph* const graph, const Vertex key_vertex, const Vertex adjacent_vertex);

/**
 * @brief Clones the contents of a graph into another graph.
 * @relates Graph
 * @param[in] graph The graph to clone from.
 * @param[out] new_graph The graph to clone to.
 */
void clone_graph(const Graph* const graph, Graph* const new_graph);

/**
 * @brief Gets the total number of adjacencies in a key led array of adjacencies.
 * @relates Graph
 * @param[in] adjacencies The key led adjacencies to get from.
 * @return The total number of adjacencies in the key led array of adjacencies.
 */
size_t get_adjacency_count(const Vertex* const adjacencies);

/**
 * @brief Checks if a key led array of adjacencies contains an adjacent vertex.
 * @relates Graph
 * @param[in] adjacencies The key led adjacencies to check against.
 * @param[in] adjacent_vertex The adjacent vertex to check for.
 * @return Whether the key led array of adjacencies contains the adjacent vertex.
 */
bool has_adjacency(const Vertex* const adjacencies, const Vertex adjacent_vertex);

/**
 * @brief Sorts the adjacency arrays by their keys alphabetically, and sorts their adjacent vertices alphabetically.
 * @relates Graph
 * @param[in,out] graph The graph to sort.
 */
void sort_adjacencies(Graph* const graph);

/** @brief An undirected connection between two vertices in a graph. */
typedef struct GraphEdge {
  /** @brief The first or source vertex of the connection. */
  Vertex source;
  /** @brief The second or destination vertex of the connection. */
  Vertex destination;
} GraphEdge;

/**
 * @brief Checks if a pair of vertices already has a corresponding edge in an array of edges.
 * @relates GraphEdge
 * @param[in] edges The edges to check against.
 * @param[in] edge_count The number of edges to check against.
 * @param[in] source_vertex The first or source vertex to check for.
 * @param[in] destination_vertex The second or destination vertex to check for.
 * @return Whether the pair of vertices has a corresponding edge in the array of edges.
 */
bool has_edge(const GraphEdge* const edges, size_t edge_count, const Vertex source_vertex,
              const Vertex destination_vertex);

/**
 * @brief Gets the edges formed by connections between adjacent vertices contained in a graph.
 * @relates GraphEdge
 * @param[in] graph The graph to get from.
 * @param[out] edges The edges of the graph.
 * @param[out] edge_count The number of edges the graph has.
 */
void get_edges(const Graph* const graph, GraphEdge* const edges, size_t* const edge_count);

#endif  // SOCIAL_NETWORK_GRAPH_H_
