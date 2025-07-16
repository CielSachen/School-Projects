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
 * @file geometry.c
 * @brief The source code containing the implementation of the geometry utility functions.
 * @copyright GNU AGPLv3
 */

#include "convex_hull/geometry.h"

#include <math.h>
#include <stdlib.h>

/**
 * @brief Calculates the distance between two points.
 * @details This uses the Pythagorean theorem to calculate the distance. The delta y and the delta x serves as the
 * height and the base.
 * @param[in] a The first point to use.
 * @param[in] b The second point to use.
 * @return The distance between the two points.
 */
double distance(const Point *const a, const Point *const b) {
    return sqrt(pow(fabs(a->x - b->x), 2) + pow(fabs(a->y - b->y), 2));
}

/**
 * @brief Calculates the polar angle of a point.
 * @details This uses the arctangent of the delta y divided by the delta x.
 * @param[in] pt The point to calculate the polar angle of.
 * @param[in] anchor_pt The anchor or origin point to use.
 * @return The polar angle of a point.
 */
double polar_angle(const Point *const pt, const Point *const anchor_pt) {
    const double angle = atan2(pt->y - anchor_pt->y, pt->x - anchor_pt->x);

    return isnan(angle) ? 0 : angle;
}

/**
 * @brief Calculates the orientation of the angle formed by connecting three points.
 * @details This uses the cross product of the two vectors formed by the three points. The result is the area of the
 * parallelogram the vectors define.
 * @param[in] a The first point to use.
 * @param[in] vertex The vertex to use.
 * @param[in] b The third point to use.
 * @return `-1` if the angle is clockwise, `1` if counter-clockwise, or `0` if collinear.
 */
int orientation(const Point *const a, const Point *const vertex, const Point *const b) {
    const double area = (vertex->x - a->x) * (b->y - a->y) - (vertex->y - a->y) * (b->x - a->x);

    return area < 0 ? -1 : area > 0 ? 1 : 0;
}
