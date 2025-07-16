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
 * @file utils.h
 * @brief The header containing the APIs of the IO utility functions.
 * @copyright GNU AGPLv3
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

#include "convex_hull/geometry.h"

/** @brief A string that can contain a maximum of 30 characters (31 including the newline character). */
typedef char String[31];

/** @brief Clears the input buffer of all characters awaiting scanning. */
void clear_input_buffer(void);

/**
 * @brief Gets a string typed input from the user.
 * @param[out] string The input received from the user.
 * @param max_length The maximum length of the output string.
 */
void get_string_input(char string[], const size_t max_length);

/**
 * @brief Prints and formats points one-by-one into a text file.
 * @param[in] output_file The text file to print into.
 * @param[in] points The points to print.
 * @param point_count The number of points to print.
 */
void print_convex_points(FILE *const output_file, const Point points[], size_t point_count);

#endif  // UTILS_H_
