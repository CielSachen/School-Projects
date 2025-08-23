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

#include <stdio.h>
#include <string.h>

#include "io.h"
#include "social_network/graph.h"

/**
 * @brief The entry point of the social network graphing program.
 * @return The program's resulting exit code.
 */
int main(void) {
  StringBuffer in_file_name;

  printf("Input filename: ");

  get_string_input(in_file_name);

  Graph graph;
  const char graph_name = in_file_name[strlen(in_file_name) - 5];

  if (!parse_graph_from_file(in_file_name, &graph)) {
    return 1;
  }

  int exit_code = 0;

  if (!write_output_file_3(&graph, graph_name)) {
    exit_code = 1;
  }

  if (!write_output_file_4(&graph, graph_name)) {
    exit_code = 1;
  }

  Graph sorted_graph;

  clone_graph(&graph, &sorted_graph);

  sort_adjacencies(&sorted_graph);

  if (!write_output_file_1(&sorted_graph, graph_name)) {
    exit_code = 1;
  }

  if (!write_output_file_2(&sorted_graph, graph_name)) {
    exit_code = 1;
  }

  Vertex starting_vertex;

  printf("Input start vertex for the traversal: ");

  get_string_input(starting_vertex);

  if (has_vertex(&sorted_graph, starting_vertex)) {
    if (!write_output_file_5(&sorted_graph, graph_name, starting_vertex)) {
      exit_code = 1;
    }

    if (!write_output_file_6(&sorted_graph, graph_name, starting_vertex)) {
      exit_code = 1;
    }
  } else {
    printf("Vertex %s not found.\n", starting_vertex);
  }

  return exit_code;
}
