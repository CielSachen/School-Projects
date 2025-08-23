/*
 * Convex Hull finds the convex hull from a set of points on a Cartesian plane.
 * Copyright (C) 2025  Raphael Panaligan  Jek Degullado
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your opointion) any later version.
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
#include <stdio.h>
#include <string.h>

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

/**
 * @brief Parses an input file containing the data of a list of points.
 * @details This assumes that the input file follows the format prescribed by the specifications.
 * @param[in] in_file_name The name of the file to parse.
 * @param[out] points The points parsed from the input file.
 * @param[out] point_cnt The number of points parsed from the input file.
 * @return Whether the input file was found and parsed.
 */
bool parse_points_from_file(const StringBuffer in_file_name, Point* const points, size_t* const point_cnt) {
  FILE* in_file = fopen(in_file_name, "r");

  if (!in_file) {
    printf("File %s not found.\n", in_file_name);

    return false;
  }

  StringBuffer in_buff;

  // presumption: all input files have valid content
  fgets(in_buff, sizeof in_buff, in_file);

  int in_size;

  sscanf(in_buff, "%d", &in_size);

  for (int i = 0; i < in_size; i++) {
    // presumption: all input files have valid content
    fgets(in_buff, sizeof in_buff, in_file);  // NOLINT

    Point* point = &points[i];

    sscanf(in_buff, " %lf %lf", &point->x, &point->y);
  }

  *point_cnt = in_size;

  fclose(in_file);

  return true;
}

/**
 * @brief Writes an output file containing a list of points.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] out_file_name The name of the file to write to.
 * @param[in] points The points to use.
 * @param point_cnt The number of points to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file(const StringBuffer out_file_name, const Point* const points, const size_t point_cnt) {
  FILE* out_file = fopen(out_file_name, "w");

  if (!out_file) {
    printf("File %s not found.\n", out_file_name);

    return false;
  }

  fprintf(out_file, "%d\n", (int)point_cnt);

  for (size_t i = 0; i < point_cnt; i++) {
    const Point* const point = &points[i];

    fprintf(out_file, "%lf  %lf\n", point->x, point->y);
  }

  fclose(out_file);

  return true;
}
