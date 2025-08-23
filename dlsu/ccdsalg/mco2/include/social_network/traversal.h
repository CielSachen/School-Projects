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
 * @file traversal.h
 * @brief The public APIs of the graph traversal helper functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifndef SOCIAL_NETWORK_TRAVERSAL_H_
#define SOCIAL_NETWORK_TRAVERSAL_H_

#include <stddef.h>

#include "graph.h"

/**
 * @brief Traverses all of a graph's connected vertices using the breadth-first search algorithm.
 * @details This will only traverse connected vertices. Vertices isolated from the starting vertex will be ignored.
 * @param[in] graph The graph to traverse.
 * @param starting_vertex The vertex to start from.
 * @param[out] visited_vertices The vertices visited during the traversal.
 * @param[out] visited_vertex_count The number of vertices visited during the traversal.
 */
void breadth_first_search(const Graph* const graph, const Vertex starting_vertex, Vertex* const visited_vertices,
                          size_t* const visited_vertex_count);

/**
 * @brief Traverses all of a graph's connected vertices using the depth-first search algorithm.
 * @details This will only traverse connected vertices. Vertices isolated from the starting vertex will be ignored.
 * @param[in] graph The graph to traverse.
 * @param starting_vertex The vertex to start from.
 * @param[out] visited_vertices The vertices visited during the traversal.
 * @param[out] visited_vertex_count The number of vertices visited during the traversal.
 */
void depth_first_search(const Graph* const graph, const Vertex starting_vertex, Vertex* const visited_vertices,
                        size_t* const visited_vertex_count);

#endif  // SOCIAL_NETWORK_TRAVERSAL_H_
