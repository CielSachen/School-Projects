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

#include "convex_hull/graham_scan1.h"

#include "convex_hull/sort.h"
#include "convex_hull/stack.h"

/**
 * @brief Scans points to find the points that would make up the convex hull using a slower sorting algorithm.
 * @details This locates the point with the lowest y-coordinate, and lowest x-coordinate if multiple, and sets it as the
 * anchor point. The points are sorted using the selection sort algorithm. Then, they are checked one-by-one for the
 * direction of the angle they form. All points starting from the anchor point that have a counter-clockwise direction
 * form the convex hull.
 * @param[in,out] points The points to scan. This will be mutated to be sorted.
 * @param point_cnt The number of points to scan.
 * @param[out] convex_points The points from the created convex set.
 * @param[out] convex_point_cnt The number of points from the created convex set.
 */
void slow_scan(Point* const points, const size_t point_cnt, Point** const convex_points,
               size_t* const convex_point_cnt) {
  size_t anchor_point_idx = 0;

  for (size_t i = 1; i < point_cnt; i++) {
    const Point* const anchor_pt = &points[anchor_point_idx];
    const Point* const pt = &points[i];

    if (pt->y < anchor_pt->y || (pt->y == anchor_pt->y && pt->x < anchor_pt->x)) {
      anchor_point_idx = i;
    }
  }

  const Point anchor_pt = points[anchor_point_idx];

  selection_sort(points, point_cnt, &anchor_pt);

  Stack stack;

  create(&stack);

  push(&stack, points[0]);
  push(&stack, points[1]);

  for (size_t i = 2; i < point_cnt; i++) {
    Point curr_point = pop(&stack);
    const Point* const next_point = &points[i];

    while (!is_empty(&stack) && orientation(top(&stack), &curr_point, next_point) <= 0) {
      curr_point = pop(&stack);
    }

    push(&stack, curr_point);
    push(&stack, *next_point);
  }

  const Point last_point = pop(&stack);

  if (orientation(top(&stack), &last_point, &anchor_pt) > 0) {
    push(&stack, last_point);
  }

  *convex_points = stack.elements;
  *convex_point_cnt = stack.top + 1;
}
