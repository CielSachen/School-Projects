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
 * @file graham_scan1.c
 * @brief The source code containing the implementation of the slow graham scan.
 * @copyright GNU AGPLv3
 */

#include "convex_hull/graham_scan1.h"

#include <stdio.h>
#include <time.h>

#include "convex_hull/sort.h"
#include "convex_hull/stack.h"

/**
 * @brief Scans points to find the points that would make up the convex hull using a slower sorting algorithm.
 * @details This locates the point with the lowest y-coordinate, and lowest x-coordinate if multiple, and sets it as the
 * anchor point. The points are sorted, using the selection sort algorithm. Then, they are checked one-by-one for the
 * direction of the angle they formed. All points, starting from the anchor point, that have a counter-clockwise
 * direction form the convex hull.
 * @param[in,out] pts The points to scan through. This will be mutated to be sorted.
 * @param pt_cnt The number of points to scan through.
 * @param[out] convex_pts The resulting points from the created convex set.
 * @param[out] convex_pt_cnt The number of resulting points from the created convex set.
 * @return Whether the scan was completed.
 */
bool slow_scan(Point pts[], const size_t pt_cnt, Point *convex_pts[], size_t *convex_pt_cnt) {
    const clock_t start_time = clock();

    size_t anchor_pt_idx = 0;

    for (size_t i = 1; i < pt_cnt; i++) {
        Point *anchor_pt = &pts[anchor_pt_idx];
        Point *pt = &pts[i];

        if (pt->y < anchor_pt->y || (pt->y == anchor_pt->y && pt->x < anchor_pt->x)) {
            anchor_pt_idx = i;
        }
    }

    const Point anchor_pt = pts[anchor_pt_idx];

    selection_sort(pts, pt_cnt, &anchor_pt);

    Stack stack;

    create(&stack);

    push(&stack, pts[0]);
    push(&stack, pts[1]);

    for (size_t i = 2; i < pt_cnt; i++) {
        Point curr_pt = pop(&stack);
        const Point next_pt = pts[i];

        while (!is_empty(&stack) && orientation(top(&stack), &curr_pt, &next_pt) <= 0) {
            curr_pt = pop(&stack);
        }

        push(&stack, curr_pt);

        if (is_full(&stack)) {
            printf("The stack has overflowed because of having too many points!\n");

            return false;
        }

        push(&stack, next_pt);
    }

    const Point last_pt = pop(&stack);

    if (orientation(top(&stack), &last_pt, &anchor_pt) > 0) {
        push(&stack, last_pt);
    }

    *convex_pts = stack.data;
    *convex_pt_cnt = stack.length;

    const clock_t end_time = clock();

    printf("Execution Time: %lfms\n", (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000);

    return true;
}
