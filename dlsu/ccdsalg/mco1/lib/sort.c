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

#include "convex_hull/sort.h"

/**
 * @brief Swaps the points of two pointers.
 * @param[in,out] a The first pointer to swap the point of.
 * @param[in,out] b The second pointer to swap the point of.
 */
void swap(Point* const a, Point* const b) {
  const Point temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * @brief Sorts points by their polar angle or distance in ascending order using the selection sort algorithm.
 * @details This sorts points by their polar angles by default. If multiple points share a polar angle, this sorts those
 * by their distances.
 * @param[in,out] points The points to sort.
 * @param point_cnt The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void selection_sort(Point* const points, const size_t point_cnt, const Point* const anchor_point) {
  for (size_t i = 0; i < point_cnt - 1; i++) {
    size_t smallest_idx = i;

    for (size_t j = i + 1; j < point_cnt; j++) {
      const Point* const sorted_pt = &points[smallest_idx];
      const double sorted_polar_angle = polar_angle(sorted_pt, anchor_point);

      const Point* const unsorted_pt = &points[j];
      const double unsorted_polar_angle = polar_angle(unsorted_pt, anchor_point);

      if (unsorted_polar_angle < sorted_polar_angle ||
          (unsorted_polar_angle == sorted_polar_angle &&
           distance(anchor_point, unsorted_pt) < distance(anchor_point, sorted_pt))) {
        smallest_idx = j;
      }
    }

    if (smallest_idx != i) {
      swap(&points[i], &points[smallest_idx]);
    }
  }
}

/**
 * @brief Checks if a point is larger than another point.
 * @details This checks if the polar angle is greater, or if the distance is greater when the polar angles are equal.
 * @param[in] a The point to check.
 * @param[in] b The point to check against.
 * @param[in] anchor_point The anchor or origin point to use.
 * @return Whether point `a` is larger than point `b`.
 */
bool is_larger(const Point* const a, const Point* const b, const Point* const anchor_point) {
  const double a_polar_angle = polar_angle(a, anchor_point);
  const double b_polar_angle = polar_angle(b, anchor_point);

  return a_polar_angle > b_polar_angle ||
         (a_polar_angle == b_polar_angle && distance(anchor_point, a) > distance(anchor_point, b));
}

/**
 * @brief Converts an array starting from a root element into a max heap.
 * @details This treats the array as the level order tree traversal sequence of a complete binary tree to build a max
 * heap.
 * @param[in,out] points The points to heapify.
 * @param point_cnt The number of points to heapify.
 * @param root_idx The index of the root point to use.
 * @param[in] anchor_point The anchor or origin point to use.
 */
static void heapify(Point* const points, const size_t point_cnt, const size_t root_idx,
                    const Point* const anchor_point) {
  size_t largest_idx = root_idx;

  const size_t left_idx = 2 * root_idx + 1;
  const size_t right_idx = 2 * root_idx + 2;

  if (left_idx < point_cnt && is_larger(&points[left_idx], &points[largest_idx], anchor_point)) {
    largest_idx = left_idx;
  }

  if (right_idx < point_cnt && is_larger(&points[right_idx], &points[largest_idx], anchor_point)) {
    largest_idx = right_idx;
  }

  if (largest_idx != root_idx) {
    swap(&points[root_idx], &points[largest_idx]);

    heapify(points, point_cnt, largest_idx, anchor_point);
  }
}

/**
 * @brief Sorts points by their polar angle or distance in ascending order using the heap sort algorithm.
 * @details This sorts points by their polar angles by default. If multiple points share a polar angle, this sorts those
 * by their distances.
 * @param[in,out] points The points to sort.
 * @param point_cnt The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void heap_sort(Point* const points, const size_t point_cnt, const Point* const anchor_point) {
  for (int i = point_cnt / 2 - 1; i >= 0; i--) {
    heapify(points, point_cnt, i, anchor_point);
  }

  for (int i = point_cnt - 1; i > 0; i--) {
    swap(&points[0], &points[i]);

    heapify(points, i, 0, anchor_point);
  }
}
