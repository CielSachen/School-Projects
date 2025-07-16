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
 * @file stack.h
 * @brief The header containing the public APIs of the sorting utility functions.
 * @copyright GNU AGPLv3
 */

#ifndef CONVEX_HULL_SORT_H_
#define CONVEX_HULL_SORT_H_

#include <stdbool.h>
#include <stddef.h>

#include "geometry.h"

/**
 * @brief Swaps the values of two pointers.
 * @param[in,out] a The first pointer to swap the value of.
 * @param[in,out] b The second pointer to swap the value of.
 */
void swap(Point *a, Point *b);

/**
 * @brief Sorts points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This uses the selection sort algorithm to sort.
 * @param[in,out] points The points to sort.
 * @param point_count The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void selection_sort(Point points[], const size_t point_count, const Point *const anchor_point);

/**
 * @brief Checks if a point is larger than another point.
 * @details This checks if the polar angle is greater, or if the distance is greater when the polar angles are equal.
 * @param[in] a The point to check.
 * @param[in] b The point to check against.
 * @param[in] anchor_point The anchor or origin point to use.
 * @return Whether the point is larger than the other point.
 */
bool is_larger(const Point *const a, const Point *const b, const Point *const anchor_point);

/**
 * @brief Heapifies points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This swaps points until all "parent nodes" are larger than their children.
 * @param[in,out] points The points to heapify.
 * @param point_count The number of points to heapify.
 * @param root_index The index of the root point to use.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void heapify(Point points[], const size_t point_count, const size_t root_index, const Point *const anchor_point);

/**
 * @brief Sorts points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This uses the heap sort algorithm to sort.
 * @param[in,out] points The points to sort.
 * @param point_count The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void heap_sort(Point points[], const size_t point_count, const Point *const anchor_point);

#endif  // CONVEX_HULL_SORT_H_
