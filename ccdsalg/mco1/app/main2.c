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
 * @file main1.c
 * @brief The source code containing the implementation of the convex hull program using a faster sorting algorithm.
 * @copyright GNU AGPLv3
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "convex_hull/graham_scan2.h"
#include "convex_hull/stack.h"
#include "utils.h"

/**
 * @brief The entry point of the convex hull program using a faster sorting algorithm.
 * @return The program’s resulting exit code.
 */
int main(void) {
    printf("Input File Name: ");

    String in_file_name;

    get_string_input(in_file_name, sizeof in_file_name);

    FILE *const in_file = fopen(in_file_name, "r");

    if (in_file == NULL) {
        perror("Failed to Read the Input File");

        return 1;
    }

    String inp_buff;

    size_t inp_size;

    if (fgets(inp_buff, sizeof inp_buff, in_file) == NULL) {
        fclose(in_file);

        printf("The input file cannot be empty!\n");

        return 1;
    }

    sscanf(inp_buff, "%zu", &inp_size);

    const size_t pts_mem_size = sizeof(Point) * inp_size;

    if (pts_mem_size > sizeof(Point) * MAX_STACK_LENGTH) {
        fclose(in_file);

        printf("The problem size is too big! The application is at risk of a stack overflow error!\n");

        return 1;
    }

    Point *pts = (Point *)malloc(pts_mem_size);

    for (size_t i = 0; i < inp_size; i++) {
        if (fgets(inp_buff, sizeof inp_buff, in_file) == NULL) {
            free(pts);

            fclose(in_file);

            printf("The number of points is less than the input size!\n");

            return 1;
        }

        Point *pt = &pts[i];

        if (sscanf(inp_buff, " %lf %lf", &pt->x, &pt->y) != 2) {
            free(pts);

            fclose(in_file);

            printf("A point has incomplete coordinates!\n");

            return 1;
        }
    }

    fclose(in_file);

    printf("\n");

    Point *convex_pts;
    size_t convex_pt_cnt;

    if (!fast_scan(pts, inp_size, &convex_pts, &convex_pt_cnt)) {
        // The prior function already prints an error message.
        return 1;
    }

    free(pts);

    printf("\n");

    printf("Output File Name: ");

    String out_file_name;

    get_string_input(out_file_name, sizeof out_file_name);

    FILE *const out_file = fopen(out_file_name, "w");

    if (out_file == NULL) {
        perror("Failed to Write the Output File");

        return 1;
    }

    print_convex_points(out_file, convex_pts, convex_pt_cnt);

    fclose(out_file);

    return 0;
}
