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
 * @file geometry.h
 * @brief The public APIs of the geometric concepts' structs and utility functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifndef CONVEX_HULL_GEOMETRY_H_
#define CONVEX_HULL_GEOMETRY_H_

/** @brief A point within a Cartesian plane. */
typedef struct Point {
  /** @brief The x-coordinate of the point. */
  double x;
  /** @brief The y-coordinate of the point. */
  double y;
} Point;

/**
 * @brief Calculates the distance between two points.
 * @details This uses the Pythagorean theorem to calculate the distance. The delta y and the delta x serves as the
 * height and the base.
 * @param[in] a The first point to use.
 * @param[in] b The second point to use.
 * @return The distance between point `a` and point `b`.
 */
double distance(const Point* const a, const Point* const b);

/**
 * @brief Calculates the orientation of the angle formed by connecting three points.
 * @details This uses the cross product of the two vectors formed by the three points to determine the orientation.
 * @param[in] vertex The vertex to use.
 * @param[in] b The third point to use.
 * @return `-1` if the angle is clockwise, `1` if counter-clockwise, or `0` if collinear.
 */
int orientation(const Point* const a, const Point* const vertex, const Point* const b);

/**
 * @brief Calculates the polar angle of a point.
 * @param[in] point The point to calculate the polar angle of.
 * @param[in] anchor_point The anchor or origin point to use.
 * @return The polar angle of a point.
 */
double polar_angle(const Point* const point, const Point* const anchor_point);

#endif  // CONVEX_HULL_GEOMETRY_H_
