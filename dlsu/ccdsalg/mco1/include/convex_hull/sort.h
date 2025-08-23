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
 * @file sort.h
 * @brief The public APIs of the array sorting helper and utility functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifndef CONVEX_HULL_SORT_H_
#define CONVEX_HULL_SORT_H_

#include <stdbool.h>
#include <stddef.h>

#include "geometry.h"

/**
 * @brief Swaps the points of two pointers.
 * @param[in,out] a The first pointer to swap the point of.
 * @param[in,out] b The second pointer to swap the point of.
 */
void swap(Point* const a, Point* const b);

/**
 * @brief Sorts points by their polar angle or distance in ascending order using the selection sort algorithm.
 * @details This sorts points by their polar angles by default. If multiple points share a polar angle, this sorts those
 * by their distances.
 * @param[in,out] points The points to sort.
 * @param point_count The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void selection_sort(Point* const points, size_t point_count, const Point* const anchor_point);

/**
 * @brief Checks if a point is larger than another point.
 * @details This checks if the polar angle is greater, or if the distance is greater when the polar angles are equal.
 * @param[in] a The point to check.
 * @param[in] b The point to check against.
 * @param[in] anchor_point The anchor or origin point to use.
 * @return Whether point `a` is larger than point `b`.
 */
bool is_larger(const Point* const a, const Point* const b, const Point* const anchor_point);

/**
 * @brief Sorts points by their polar angle or distance in ascending order using the heap sort algorithm.
 * @details This sorts points by their polar angles by default. If multiple points share a polar angle, this sorts those
 * by their distances.
 * @param[in,out] points The points to sort.
 * @param point_count The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void heap_sort(Point* const points, size_t point_count, const Point* const anchor_point);

#endif  // CONVEX_HULL_SORT_H_
