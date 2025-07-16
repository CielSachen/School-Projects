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

/**
 * @file sort.c
 * @brief The source code containing the implementation of the sorting utility functions.
 * @copyright GNU AGPLv3
 */

#include "convex_hull/sort.h"

/**
 * @brief Swaps the values of two pointers.
 * @param[in,out] a The first pointer to swap the value of.
 * @param[in,out] b The second pointer to swap the value of.
 */
void swap(Point *a, Point *b) {
    const Point temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sorts points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This uses the selection sort algorithm to sort.
 * @param[in,out] pts The points to sort.
 * @param pt_cnt The number of points to sort.
 * @param[in] anchor_pt The anchor or origin point to use.
 */
void selection_sort(Point pts[], const size_t pt_cnt, const Point *const anchor_pt) {
    for (size_t i = 0; i < pt_cnt - 1; i++) {
        size_t smallest_idx = i;

        for (size_t j = i + 1; j < pt_cnt; j++) {
            const Point *const sorted_pt = &pts[smallest_idx];
            const double sorted_polar_angle = polar_angle(sorted_pt, anchor_pt);

            const Point *const unsorted_pt = &pts[j];
            const double unsorted_polar_angle = polar_angle(unsorted_pt, anchor_pt);

            if (unsorted_polar_angle < sorted_polar_angle ||
                (unsorted_polar_angle == sorted_polar_angle &&
                 distance(anchor_pt, unsorted_pt) < distance(anchor_pt, sorted_pt))) {
                smallest_idx = j;
            }
        }

        if (smallest_idx != i) {
            swap(&pts[i], &pts[smallest_idx]);
        }
    }
}

/**
 * @brief Checks if a point is larger than another point.
 * @details This checks if the polar angle is greater, or if the distance is greater when the polar angles are equal.
 * @param[in] a The point to check.
 * @param[in] b The point to check against.
 * @param[in] anchor_pt The anchor or origin point to use.
 * @return Whether the point is larger than the other point.
 */
bool is_larger(const Point *const a, const Point *const b, const Point *const anchor_pt) {
    const double a_polar_angle = polar_angle(a, anchor_pt);
    const double b_polar_angle = polar_angle(b, anchor_pt);

    return a_polar_angle > b_polar_angle ||
           (a_polar_angle == b_polar_angle && distance(anchor_pt, a) > distance(anchor_pt, b));
}

/**
 * @brief Heapifies points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This swaps points until all "parent nodes" are larger than their children.
 * @param[in,out] pts The points to heapify.
 * @param pt_cnt The number of points to heapify.
 * @param root_idx The index of the root point to use.
 * @param[in] anchor_pt The anchor or origin point to use.
 */
void heapify(Point pts[], const size_t pt_cnt, const size_t root_idx, const Point *const anchor_pt) {
    size_t largest_idx = root_idx;

    const size_t left_idx = 2 * root_idx + 1;

    if (left_idx < pt_cnt && is_larger(&pts[left_idx], &pts[largest_idx], anchor_pt)) {
        largest_idx = left_idx;
    }

    const size_t right_idx = 2 * root_idx + 2;

    if (right_idx < pt_cnt && is_larger(&pts[right_idx], &pts[largest_idx], anchor_pt)) {
        largest_idx = right_idx;
    }

    if (largest_idx != root_idx) {
        swap(&pts[root_idx], &pts[largest_idx]);

        heapify(pts, pt_cnt, largest_idx, anchor_pt);
    }
}

/**
 * @brief Sorts points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This uses the heap sort algorithm to sort.
 * @param[in,out] pts The points to sort.
 * @param pt_cnt The number of points to sort.
 * @param[in] anchor_pt The anchor or origin point to use.
 */
void heap_sort(Point pts[], const size_t pt_cnt, const Point *const anchor_pt) {
    for (int i = pt_cnt / 2 - 1; i >= 0; i--) {
        heapify(pts, pt_cnt, i, anchor_pt);
    }

    for (int i = pt_cnt - 1; i > 0; i--) {
        swap(&pts[0], &pts[i]);

        heapify(pts, i, 0, anchor_pt);
    }
}
