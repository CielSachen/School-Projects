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
 * @file utils.c
 * @brief The source code containing the implementation of the IO utility functions.
 * @copyright GNU AGPLv3
 */

#include "utils.h"

#include <string.h>

/** @brief Clears the input buffer of all characters awaiting scanning. */
void clear_input_buffer(void) {
    int excess_char;

    while ((excess_char = getchar()) != '\n' && excess_char != EOF) {
    }
}

/**
 * @brief Gets a string typed input from the user.
 * @param[out] str The input received from the user.
 * @param max_len The maximum length of the output string.
 */
void get_string_input(char str[], const size_t max_len) {
    fflush(stdout);

    fgets(str, max_len, stdin);

    const size_t last_idx = strlen(str) - 1;

    if (str[last_idx] == '\n') {
        str[last_idx] = '\0';
    } else {
        clear_input_buffer();
    }
}

/**
 * @brief Prints and formats points one-by-one into a text file.
 * @param[in] out_file The text file to print into.
 * @param[in] pts The points to print.
 * @param pt_cnt The number of points to print.
 */
void print_convex_points(FILE *const out_file, const Point pts[], size_t pt_cnt) {
    fprintf(out_file, "%zu\n", pt_cnt);

    for (size_t i = 0; i < pt_cnt; i++) {
        const Point *const pt = &pts[i];

        fprintf(out_file, "%11.6lf  %11.6lf\n", pt->x, pt->y);
    }
}
