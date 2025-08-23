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
 * @brief The entry point of the bonus social network graphing program.
 * @return The program's resulting exit code.
 */
int main(void) {
  StringBuffer in_file_name;

  printf("Input filename (Parent graph): ");

  get_string_input(in_file_name);

  Graph graph;
  const char graph_name = in_file_name[strlen(in_file_name) - 5];

  if (!parse_graph_from_file(in_file_name, &graph)) {
    return 1;
  }

  sort_adjacencies(&graph);

  printf("Input filename (Subgraph): ");

  get_string_input(in_file_name);

  Graph subgraph;
  const char subgraph_name = in_file_name[strlen(in_file_name) - 5];

  if (!parse_graph_from_file(in_file_name, &subgraph)) {
    return 1;
  }

  sort_adjacencies(&subgraph);

  if (!write_output_file_7(&graph, graph_name, &subgraph, subgraph_name)) {
    return 1;
  }

  return 0;
}
