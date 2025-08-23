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
 * @file utils.h
 * @brief The public APIs of the Input/Output helper and utility functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifndef IO_H_
#define IO_H_

#include <stdbool.h>
#include <stddef.h>

#include "social_network/graph.h"

/** @brief The maximum number of characters a string input operation will handle. */
#define BUFFER_SIZE 64

/** @brief A string that can contain the `BUFFER_SIZE` and a null character ending (`BUFFER_SIZE + 1`). */
typedef char StringBuffer[BUFFER_SIZE + 1];

/**
 * @brief Gets a string typed input from the user.
 * @param[out] string The input received from the user.
 */
void get_string_input(StringBuffer string);

/** @brief The delimiter to use when tokenizing strings to exclude whitespace characters. */
extern const char* WHITESPACE_DELIMITER;

/** @brief The vertex label used to represent NULL, or the end of the list. */
extern const char* NULL_VERTEX_LABEL;

/**
 * @brief Parses an input file containing the data of a graph represented in an adjacency list.
 * @details This assumes that the input file follows the format prescribed by the specifications.
 * @param[in] input_file_name The name of the file to parse.
 * @param[out] graph The graph parsed from the input file.
 * @return Whether the input file was found and parsed.
 */
bool parse_graph_from_file(const StringBuffer input_file_name, Graph* const graph);

/**
 * @brief Writes an output file containing a graph's vertex labels and edges.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_1(const Graph* const graph, const char graph_name);

/**
 * @brief Writes an output file containing the degrees of a graph's vertices.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_2(const Graph* const graph, const char graph_name);

/**
 * @brief Writes an output file containing the adjacency list representation of a graph.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_3(const Graph* const graph, const char graph_name);

/**
 * @brief Writes an output file containing the adjacency matrix representation of a graph.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_4(const Graph* const graph, const char graph_name);

/**
 * @brief Writes an output file containing the non-repeating traversal sequence of a graph using breadth-first search.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] starting_vertex The vertex to start the traversal from.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_5(const Graph* const graph, const char graph_name, const Vertex starting_vertex);

/**
 * @brief Writes an output file containing the non-repeating traversal sequence of a graph using depth-first search.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] starting_vertex The vertex to start the traversal from.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_6(const Graph* const graph, const char graph_name, const Vertex starting_vertex);

/**
 * @brief Writes an output file containing the step-by-step check of whether a graph is a subgraph of another.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] subgraph The subgraph to use.
 * @param[in] subgraph_name The name of the subgraph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_7(const Graph* const graph, const char graph_name, const Graph* const subgraph,
                         const char subgraph_name);

#endif  // IO_H_
