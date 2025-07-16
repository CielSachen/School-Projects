extern "C" {
#include "convex_hull/geometry.h"
}

#include <gtest/gtest.h>

#include <cmath>

TEST(Distance, ReturnsTheDistanceBetweenAAndB) {
    const Point a = {-2, 3};
    const Point b = {4, -7};

    EXPECT_EQ(distance(&a, &b), 11.661903789690601);
}

TEST(PolarAngle, ReturnsThePolarAngleOfThePoint) {
    const Point pt = {3, 4};
    const Point anchor_pt = {0, 0};

    EXPECT_EQ(polar_angle(&pt, &anchor_pt), 0.92729521800161219);
}

TEST(PolarAngle, ReturnsZeroIfThePolarAngleIsNan) {
    const Point pt = {3, 4};
    const Point anchor_pt = {0, NAN};

    EXPECT_EQ(polar_angle(&pt, &anchor_pt), 0);
}

TEST(Orientation, ReturnsNegativeOneIfTheAngleIsClockwise) {
    const Point a = {0, 0};
    const Point b = {2, 3};
    const Point c = {4, 5};

    EXPECT_EQ(orientation(&a, &b, &c), -1);
}

TEST(Orientation, ReturnsOneIfTheAngleIsCounterClockwise) {
    const Point a = {0, 0};
    const Point b = {2, 3};
    const Point c = {0, 5};

    EXPECT_EQ(orientation(&a, &b, &c), 1);
}

TEST(Orientation, ReturnsZeroIfTheAngleIsCollinear) {
    const Point a = {0, 0};
    const Point b = {2, 3};
    const Point c = {4, 6};

    EXPECT_EQ(orientation(&a, &b, &c), 0);
}
