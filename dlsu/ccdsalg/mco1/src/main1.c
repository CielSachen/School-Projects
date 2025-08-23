/*
 * Convex Hull finds the convex hull from a set of points on a Cartesian plane.
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
#include <time.h>

#include "convex_hull/graham_scan1.h"
#include "convex_hull/stack.h"
#include "io.h"

/**
 * @brief The entry point of the convex hull calculator program with a slower sorting algorithm.
 * @return The program's resulting exit code.
 */
int main(void) {
  printf("Input filename: ");

  StringBuffer in_file_name;

  get_string_input(in_file_name);

  Point points[MAX_STACK_SIZE];
  size_t point_cnt;

  if (!parse_points_from_file(in_file_name, points, &point_cnt)) {
    return 1;
  }

  Point* convex_points;
  size_t convex_point_cnt;

  const clock_t start_clock = clock();

  slow_scan(points, point_cnt, &convex_points, &convex_point_cnt);

  printf("Execution time: %lfms\n", (double)(clock() - start_clock) / CLOCKS_PER_SEC * 1000);

  printf("Output filename: ");

  StringBuffer out_file_name;

  get_string_input(out_file_name);

  if (!write_output_file(out_file_name, convex_points, convex_point_cnt)) {
    return 1;
  }

  return 0;
}
