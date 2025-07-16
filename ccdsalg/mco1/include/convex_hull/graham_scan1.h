/*
 * CConvex Hull finds the convex hull from a set of points on a Cartesian plane.
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
 * @file graham_scan1.h
 * @brief The header containing the public API of the slow graham scan.
 * @copyright GNU AGPLv3
 */

#ifndef CONVEX_HULL_GRAHAM_SCAN1_H_
#define CONVEX_HULL_GRAHAM_SCAN1_H_

#include <stdbool.h>
#include <stddef.h>

#include "geometry.h"

/**
 * @brief Scans points to find the points that would make up the convex hull using a slower sorting algorithm.
 * @details This locates the point with the lowest y-coordinate, and lowest x-coordinate if multiple, and sets it as the
 * anchor point. The points are sorted, using the selection sort algorithm. Then, they are checked one-by-one for the
 * direction of the angle they formed. All points, starting from the anchor point, that have a counter-clockwise
 * direction form the convex hull.
 * @param[in,out] points The points to scan through. This will be mutated to be sorted.
 * @param point_count The number of points to scan through.
 * @param[out] convex_points The resulting points from the created convex set.
 * @param[out] convex_point_count The number of resulting points from the created convex set.
 * @return Whether the scan was completed.
 */
bool slow_scan(Point points[], const size_t point_count, Point *convex_points[], size_t *convex_point_count);

#endif  // CONVEX_HULL_GRAHAM_SCAN1_H_
