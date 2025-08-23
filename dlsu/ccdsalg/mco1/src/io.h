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
 * @file utils.h
 * @brief The public APIs of the Input/Output helper and utility functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifndef IO_H_
#define IO_H_

#include <stdbool.h>
#include <stddef.h>

#include "convex_hull/geometry.h"

/** @brief The maximum number of characters a string input operation will handle. */
#define BUFFER_SIZE 32

/** @brief A string that can contain the `BUFFER_SIZE` and a null character ending (`BUFFER_SIZE + 1`). */
typedef char StringBuffer[BUFFER_SIZE + 1];

/**
 * @brief Gets a string typed input from the user.
 * @param[out] string The input received from the user.
 */
void get_string_input(StringBuffer string);

/**
 * @brief Parses an input file containing the data of a list of points.
 * @details This assumes that the input file follows the format prescribed by the specifications.
 * @param[in] input_file_name The name of the file to parse.
 * @param[out] points The points parsed from the input file.
 * @param[out] point_count The number of points parsed from the input file.
 * @return Whether the input file was found and parsed.
 */
bool parse_points_from_file(const StringBuffer input_file_name, Point* const points, size_t* const point_count);

/**
 * @brief Writes an output file containing a list of points.
 * @details This writes to the file following the format prescribed by the specifications.
 * @param[in] output_file_name The name of the file to write to.
 * @param[in] points The points to use.
 * @param point_count The number of points to use.
 * @return Whether the output file was found and written to.
 */
bool write_output_file(const StringBuffer output_file_name, const Point* const points, size_t point_count);

#endif  // IO_H_
