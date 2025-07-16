extern "C" {
#include "convex_hull/sort.h"
}

#include <gtest/gtest.h>

#include <algorithm>

#define ARRAY_LENGTH 10

Point POINTS[ARRAY_LENGTH] = {{7, 5}, {5, 8}, {8, 1}, {1, 6}, {6, 0}, {3, 9}, {9, 4}, {4, 10}, {8, 6}, {2, 0}};
Point *const ANCHOR_POINT = &POINTS[9];

void expect_sorted(const Point pts[]) {
    for (std::size_t i = 0; i < ARRAY_LENGTH - 1; i++) {
        const Point *const curr_pt = &pts[i];
        const double curr_polar_angle = polar_angle(curr_pt, ANCHOR_POINT);
        const Point *const next_pt = &pts[i + 1];
        const double next_polar_angle = polar_angle(next_pt, ANCHOR_POINT);

        if (curr_polar_angle == next_polar_angle) {
            EXPECT_LT(distance(ANCHOR_POINT, curr_pt), distance(ANCHOR_POINT, next_pt));
        } else {
            EXPECT_LT(curr_polar_angle, next_polar_angle);
        }
    }
}

TEST(Swap, SwapsValues) {
    const Point first_val = {0, 0};
    Point swappable_first_val = first_val;
    const Point second_val = {1, 1};
    Point swappable_second_val = second_val;

    swap(&swappable_first_val, &swappable_second_val);

    EXPECT_EQ(swappable_first_val.x, second_val.x);
    EXPECT_EQ(swappable_first_val.y, second_val.y);
    EXPECT_EQ(swappable_second_val.x, first_val.x);
    EXPECT_EQ(swappable_second_val.y, first_val.y);
}

TEST(SelectionSort, SortsElementsIntoIncreasingOrder) {
    Point pts[ARRAY_LENGTH];

    std::copy(POINTS, POINTS + ARRAY_LENGTH, pts);

    selection_sort(pts, ARRAY_LENGTH, ANCHOR_POINT);

    expect_sorted(pts);
}

TEST(IsLarger, ReturnsTrueIfAHasLargerPolarAngle) {
    const Point *const a = &POINTS[1];
    const Point *const b = &POINTS[0];

    EXPECT_TRUE(is_larger(a, b, ANCHOR_POINT));
}

TEST(IsLarger, ReturnsTrueIfAHasEqualPolarAngleAndLargerDistance) {
    const Point *const a = &POINTS[8];
    const Point *const b = &POINTS[0];

    EXPECT_TRUE(is_larger(a, b, ANCHOR_POINT));
}

TEST(IsLarger, ReturnsFalseIfAHasSmallerPolarAngle) {
    const Point *const a = &POINTS[0];
    const Point *const b = &POINTS[1];

    EXPECT_FALSE(is_larger(a, b, ANCHOR_POINT));
}

TEST(IsLarger, ReturnsFalseIfAHasEqualPolarAngleAndSmallerDistance) {
    const Point *const a = &POINTS[0];
    const Point *const b = &POINTS[8];

    EXPECT_FALSE(is_larger(a, b, ANCHOR_POINT));
}

TEST(HeapSort, SortsElementsIntoIncreasingOrder) {
    Point pts[ARRAY_LENGTH];

    std::copy(POINTS, POINTS + ARRAY_LENGTH, pts);

    heap_sort(pts, ARRAY_LENGTH, ANCHOR_POINT);

    expect_sorted(pts);
}
