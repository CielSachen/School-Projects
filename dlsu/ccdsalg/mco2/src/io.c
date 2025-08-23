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

#include "io.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "social_network/traversal.h"

/**
 * @brief Gets a string typed input from the user.
 * @param[out] str The input received from the user.
 */
void get_string_input(StringBuffer str) {
  fflush(stdout);

  fgets(str, BUFFER_SIZE, stdin);

  size_t last_idx = strlen(str) - 1;

  if (str[last_idx] != '\n') {
    int excess_char;

    while ((excess_char = getchar()) != '\n' && excess_char != EOF);
  }

  while (last_idx >= 0 && isspace(str[last_idx])) {
    str[last_idx--] = '\0';
  }
}

/** @brief The delimiter to use when tokenizing strings to exclude whitespace characters. */
const char* WHITESPACE_DELIMITER = " \f\n\r\t\v";

/** @brief The vertex label used to represent NULL, or the end of the list. */
const char* NULL_VERTEX_LABEL = "-1";

/**
 * @brief Parses an input file containing the data of a graph represented in an adjacency list.
 * @details This assumes that the input file follows the format prescribed by the specifications.
 * @param[in] input_file_name The name of the file to parse.
 * @param[out] graph The graph parsed from the input file.
 * @return Whether the input file was found and parsed.
 */
bool parse_graph_from_file(const StringBuffer in_file_name, Graph* const graph) {
  FILE* file = fopen(in_file_name, "r");

  if (!file) {
    printf("File %s not found.\n", in_file_name);

    return false;
  }

  StringBuffer in_buff;

  // presumption: all input files have valid content
  fgets(in_buff, sizeof in_buff, file);  // NOLINT

  int vertex_cnt;

  sscanf(in_buff, "%d", &vertex_cnt);

  initialize_graph(graph, vertex_cnt);

  for (int i = 0; i < vertex_cnt; i++) {
    // presumption: all input files have valid content
    fgets(in_buff, sizeof in_buff, file);  // NOLINT

    Vertex vertex;
    char* adjacent_vertex = strtok(in_buff, WHITESPACE_DELIMITER);

    strncpy(vertex, adjacent_vertex, MAX_VERTEX_LABEL_LENGTH);

    adjacent_vertex = strtok(NULL, WHITESPACE_DELIMITER);

    while (adjacent_vertex != NULL) {
      if (strncmp(adjacent_vertex, NULL_VERTEX_LABEL, MAX_VERTEX_LABEL_LENGTH) == 0) {
        if (!has_vertex(graph, vertex)) {
          add_adjacency(graph, vertex, NULL);
        }

        break;
      }

      add_adjacency(graph, vertex, adjacent_vertex);

      adjacent_vertex = strtok(NULL, WHITESPACE_DELIMITER);
    }
  }

  fclose(file);

  return true;
}

/**
 * @brief Writes an output file containing a graph's vertex labels and edges.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_1(const Graph* const graph, const char graph_name) {
  StringBuffer out_file_name;

  sprintf(out_file_name, "%c-SET.txt", graph_name);

  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  fprintf(out_file, "V(%c)={", graph_name);

  for (size_t i = 0; i < graph->order; i++) {
    fprintf(out_file, "%s", graph->adjacencies_by_vertex[i][0]);

    if (i < graph->order - 1) {
      fprintf(out_file, ",");
    }
  }

  fprintf(out_file, "}\n");

  fprintf(out_file, "E(%c)={", graph_name);

  size_t graph_edge_cnt = powl(graph->order, 2);
  GraphEdge graph_edges[graph_edge_cnt];

  get_edges(graph, graph_edges, &graph_edge_cnt);

  for (size_t i = 0; i < graph_edge_cnt; i++) {
    const GraphEdge* const graph_edge = &graph_edges[i];

    fprintf(out_file, "(%s,%s)", graph_edge->source, graph_edge->destination);

    if (i < graph_edge_cnt - 1) {
      fprintf(out_file, ",");
    }
  }

  fprintf(out_file, "}\n");

  fclose(out_file);

  return true;
}

/**
 * @brief Writes an output file containing the degrees of a graph's vertices.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_2(const Graph* const graph, const char graph_name) {
  StringBuffer out_file_name;

  sprintf(out_file_name, "%c-DEGREE.txt", graph_name);

  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  for (size_t i = 0; i < graph->order; i++) {
    fprintf(out_file, "%*s %d\n", -MAX_VERTEX_LABEL_LENGTH, graph->adjacencies_by_vertex[i][0],
            (int)get_adjacency_count(graph->adjacencies_by_vertex[i]));
  }

  fclose(out_file);

  return true;
}

/**
 * @brief Writes an output file containing the adjacency list representation of a graph.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_3(const Graph* const graph, const char graph_name) {
  StringBuffer out_file_name;

  sprintf(out_file_name, "%c-LIST.txt", graph_name);

  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  for (size_t i = 0; i < graph->order; i++) {
    for (size_t j = 0; j < graph->order; j++) {
      if (strlen(graph->adjacencies_by_vertex[i][j]) == 0) {
        break;
      }

      fprintf(out_file, "%s->", graph->adjacencies_by_vertex[i][j]);
    }

    fprintf(out_file, "\\\n");
  }

  fclose(out_file);

  return true;
}

/**
 * @brief Writes an output file containing the adjacency matrix representation of a graph.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_4(const Graph* const graph, const char graph_name) {
  StringBuffer out_file_name;

  sprintf(out_file_name, "%c-MATRIX.txt", graph_name);

  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  fprintf(out_file, "%*s", MAX_VERTEX_LABEL_LENGTH, " ");

  for (size_t i = 0; i < graph->order; i++) {
    fprintf(out_file, " %s", graph->adjacencies_by_vertex[i][0]);
  }

  fprintf(out_file, "\n");

  for (size_t i = 0; i < graph->order; i++) {
    fprintf(out_file, "%*s", -MAX_VERTEX_LABEL_LENGTH, graph->adjacencies_by_vertex[i][0]);

    for (size_t j = 0; j < graph->order; j++) {
      fprintf(out_file, " %*d", -(int)strlen(graph->adjacencies_by_vertex[j][0]),
              has_adjacency(graph->adjacencies_by_vertex[i], graph->adjacencies_by_vertex[j][0]));
    }

    fprintf(out_file, "\n");
  }

  fclose(out_file);

  return true;
}

/**
 * @brief Writes an output file containing the non-repeating traversal sequence of a graph using breadth-first search.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] starting_vertex The vertex to start the traversal from.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_5(const Graph* const graph, const char graph_name, const Vertex starting_vertex) {
  StringBuffer out_file_name;

  sprintf(out_file_name, "%c-BFS.txt", graph_name);

  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  Vertex visited_vertices[graph->order];
  size_t visited_vertex_cnt = 0;

  breadth_first_search(graph, starting_vertex, visited_vertices, &visited_vertex_cnt);

  for (size_t i = 0; i < visited_vertex_cnt; i++) {
    fprintf(out_file, "%s", visited_vertices[i]);

    fprintf(out_file, i < visited_vertex_cnt - 1 ? " " : "\n");
  }

  fclose(out_file);

  return true;
}

/**
 * @brief Writes an output file containing the non-repeating traversal sequence of a graph using depth-first search.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] starting_vertex The vertex to start the traversal from.
 * @return Whether the output file was found and written to.
 */
bool write_output_file_6(const Graph* const graph, const char graph_name, const Vertex starting_vertex) {
  StringBuffer out_file_name;

  sprintf(out_file_name, "%c-DFS.txt", graph_name);

  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  Vertex visited_vertices[graph->order];
  size_t visited_vertex_cnt = 0;

  depth_first_search(graph, starting_vertex, visited_vertices, &visited_vertex_cnt);

  for (size_t i = 0; i < visited_vertex_cnt; i++) {
    fprintf(out_file, "%s", visited_vertices[i]);

    fprintf(out_file, i < visited_vertex_cnt - 1 ? " " : "\n");
  }

  fclose(out_file);

  return true;
}

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
                         const char subgraph_name) {
  StringBuffer out_file_name;

  sprintf(out_file_name, "%c-%c-SUBGRAPH.txt", graph_name, subgraph_name);

  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  size_t matching_vertex_cnt = 0;

  for (size_t i = 0; i < subgraph->order; i++) {
    const bool is_matching_vertex = has_vertex(graph, subgraph->adjacencies_by_vertex[i][0]);

    fprintf(out_file, "%s %c\n", subgraph->adjacencies_by_vertex[i][0], is_matching_vertex ? '+' : '-');

    if (is_matching_vertex) {
      matching_vertex_cnt++;
    }
  }

  size_t subgraph_edge_cnt = powl(subgraph->order, 2);
  GraphEdge subgraph_edges[subgraph_edge_cnt];

  get_edges(subgraph, subgraph_edges, &subgraph_edge_cnt);

  size_t graph_edge_cnt = powl(graph->order, 2);
  GraphEdge graph_edges[graph_edge_cnt];

  get_edges(graph, graph_edges, &graph_edge_cnt);

  size_t matching_edge_cnt = 0;

  for (size_t i = 0; i < subgraph_edge_cnt; i++) {
    const GraphEdge* const subgraph_edge = &subgraph_edges[i];

    const bool is_matching_edge =
      has_edge(graph_edges, graph_edge_cnt, subgraph_edge->source, subgraph_edge->destination);

    fprintf(out_file, "(%s,%s) %c\n", subgraph_edge->source, subgraph_edge->destination, is_matching_edge ? '+' : '-');

    if (is_matching_edge) {
      matching_edge_cnt++;
    }
  }

  fprintf(out_file, "%c is %s subgraph of %c.\n", subgraph_name,
          matching_vertex_cnt == subgraph->order && matching_edge_cnt == subgraph_edge_cnt ? "a" : "not a", graph_name);

  fclose(out_file);

  return true;
}
