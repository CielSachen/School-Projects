extern "C" {
#include "convex_hull/graham_scan1.h"
#include "convex_hull/graham_scan2.h"
}

#include <gtest/gtest.h>

#define STANDARD_POINT_COUNT 9
#define STANDARD_CONVEX_POINT_COUNT 5

#define CIRCLE_POINT_COUNT 72

Point STANDARD_POINTS[STANDARD_POINT_COUNT] = {{5.0, 5.0}, {10.0, 2.5}, {5.0, 10.0}, {10.0, 0.0}, {7.5, 0.0},
                                               {5.0, 0.0}, {0.0, 0.0},  {1.0, 8.0},  {0.0, 10.0}};
Point STANDARD_CONVEX_POINTS[STANDARD_CONVEX_POINT_COUNT] = {
    {0.000000, 0.000000}, {10.000000, 0.000000}, {10.000000, 2.500000}, {5.000000, 10.000000}, {0.000000, 10.000000}};

Point CIRCLE_POINTS[CIRCLE_POINT_COUNT] = {
    {2.000000, 0.000000},   {1.992389, 0.174311},   {1.969616, 0.347296},   {1.931852, 0.517638},
    {1.879385, 0.684040},   {1.812616, 0.845237},   {1.732051, 1.000000},   {1.638304, 1.147153},
    {1.532089, 1.285575},   {1.414214, 1.414214},   {1.285575, 1.532089},   {1.147153, 1.638304},
    {1.000000, 1.732051},   {0.845237, 1.812616},   {0.684040, 1.879385},   {0.517638, 1.931852},
    {0.347296, 1.969616},   {0.174311, 1.992389},   {0.000000, 2.000000},   {-0.174311, 1.992389},
    {-0.347296, 1.969616},  {-0.517638, 1.931852},  {-0.684040, 1.879385},  {-0.845237, 1.812616},
    {-1.000000, 1.732051},  {-1.147153, 1.638304},  {-1.285575, 1.532089},  {-1.414214, 1.414214},
    {-1.532089, 1.285575},  {-1.638304, 1.147153},  {-1.732051, 1.000000},  {-1.812616, 0.845237},
    {-1.879385, 0.684040},  {-1.931852, 0.517638},  {-1.969616, 0.347296},  {-1.992389, 0.174311},
    {-2.000000, 0.000000},  {-1.992389, -0.174311}, {-1.969616, -0.347296}, {-1.931852, -0.517638},
    {-1.879385, -0.684040}, {-1.812616, -0.845237}, {-1.732051, -1.000000}, {-1.638304, -1.147153},
    {-1.532089, -1.285575}, {-1.414214, -1.414214}, {-1.285575, -1.532089}, {-1.147153, -1.638304},
    {-1.000000, -1.732051}, {-0.845237, -1.812616}, {-0.684040, -1.879385}, {-0.517638, -1.931852},
    {-0.347296, -1.969616}, {-0.174311, -1.992389}, {0.000000, -2.000000},  {0.174311, -1.992389},
    {0.347296, -1.969616},  {0.517638, -1.931852},  {0.684040, -1.879385},  {0.845237, -1.812616},
    {1.000000, -1.732051},  {1.147153, -1.638304},  {1.285575, -1.532089},  {1.414214, -1.414214},
    {1.532089, -1.285575},  {1.638304, -1.147153},  {1.732051, -1.000000},  {1.812616, -0.845237},
    {1.879385, -0.684040},  {1.931852, -0.517638},  {1.969616, -0.347296},  {1.992389, -0.174311}};
Point CIRCLE_CONVEX_POINTS[CIRCLE_POINT_COUNT] = {
    {0.000000, -2.000000},  {0.174311, -1.992389},  {0.347296, -1.969616},  {0.517638, -1.931852},
    {0.684040, -1.879385},  {0.845237, -1.812616},  {1.000000, -1.732051},  {1.147153, -1.638304},
    {1.285575, -1.532089},  {1.414214, -1.414214},  {1.532089, -1.285575},  {1.638304, -1.147153},
    {1.732051, -1.000000},  {1.812616, -0.845237},  {1.879385, -0.684040},  {1.931852, -0.517638},
    {1.969616, -0.347296},  {1.992389, -0.174311},  {2.000000, 0.000000},   {1.992389, 0.174311},
    {1.969616, 0.347296},   {1.931852, 0.517638},   {1.879385, 0.684040},   {1.812616, 0.845237},
    {1.732051, 1.000000},   {1.638304, 1.147153},   {1.532089, 1.285575},   {1.414214, 1.414214},
    {1.285575, 1.532089},   {1.147153, 1.638304},   {1.000000, 1.732051},   {0.845237, 1.812616},
    {0.684040, 1.879385},   {0.517638, 1.931852},   {0.347296, 1.969616},   {0.174311, 1.992389},
    {0.000000, 2.000000},   {-0.174311, 1.992389},  {-0.347296, 1.969616},  {-0.517638, 1.931852},
    {-0.684040, 1.879385},  {-0.845237, 1.812616},  {-1.000000, 1.732051},  {-1.147153, 1.638304},
    {-1.285575, 1.532089},  {-1.414214, 1.414214},  {-1.532089, 1.285575},  {-1.638304, 1.147153},
    {-1.732051, 1.000000},  {-1.812616, 0.845237},  {-1.879385, 0.684040},  {-1.931852, 0.517638},
    {-1.969616, 0.347296},  {-1.992389, 0.174311},  {-2.000000, 0.000000},  {-1.992389, -0.174311},
    {-1.969616, -0.347296}, {-1.931852, -0.517638}, {-1.879385, -0.684040}, {-1.812616, -0.845237},
    {-1.732051, -1.000000}, {-1.638304, -1.147153}, {-1.532089, -1.285575}, {-1.414214, -1.414214},
    {-1.285575, -1.532089}, {-1.147153, -1.638304}, {-1.000000, -1.732051}, {-0.845237, -1.812616},
    {-0.684040, -1.879385}, {-0.517638, -1.931852}, {-0.347296, -1.969616}, {-0.174311, -1.992389}};

void expect_equal_arrays(const Point a[], const Point b[], const std::size_t pt_cnt) {
    for (std::size_t i = 0; i < pt_cnt; i++) {
        const Point *const pt = &a[i];
        const Point *const expected_pt = &b[i];

        EXPECT_EQ(pt->x, expected_pt->x);
        EXPECT_EQ(pt->y, expected_pt->y);
    }
}

TEST(SlowScan, GetsConvexSet) {
    Point pts[STANDARD_POINT_COUNT];

    std::copy(STANDARD_POINTS, STANDARD_POINTS + STANDARD_POINT_COUNT, pts);

    Point *convex_pts;
    size_t convex_pnt_cnt;

    bool is_successful = slow_scan(pts, STANDARD_POINT_COUNT, &convex_pts, &convex_pnt_cnt);

    EXPECT_TRUE(is_successful);

    expect_equal_arrays(convex_pts, STANDARD_CONVEX_POINTS, STANDARD_CONVEX_POINT_COUNT);
}

TEST(SlowScan, GetsConvexSetOfACircle) {
    Point pts[CIRCLE_POINT_COUNT];

    std::copy(CIRCLE_POINTS, CIRCLE_POINTS + CIRCLE_POINT_COUNT, pts);

    Point *convex_pts;
    size_t convex_pnt_cnt;

    bool is_successful = slow_scan(pts, CIRCLE_POINT_COUNT, &convex_pts, &convex_pnt_cnt);

    EXPECT_TRUE(is_successful);

    expect_equal_arrays(convex_pts, CIRCLE_CONVEX_POINTS, CIRCLE_POINT_COUNT);
}

TEST(FastScan, GetsConvexSet) {
    Point pts[STANDARD_POINT_COUNT];

    std::copy(STANDARD_POINTS, STANDARD_POINTS + STANDARD_POINT_COUNT, pts);

    Point *convex_pts;
    size_t convex_pnt_cnt;

    bool is_successful = fast_scan(pts, STANDARD_POINT_COUNT, &convex_pts, &convex_pnt_cnt);

    EXPECT_TRUE(is_successful);

    expect_equal_arrays(convex_pts, STANDARD_CONVEX_POINTS, STANDARD_CONVEX_POINT_COUNT);
}

TEST(FastScan, GetsConvexSetOfACircle) {
    Point pts[CIRCLE_POINT_COUNT];

    std::copy(CIRCLE_POINTS, CIRCLE_POINTS + CIRCLE_POINT_COUNT, pts);

    Point *convex_pts;
    size_t convex_pnt_cnt;

    bool is_successful = fast_scan(pts, CIRCLE_POINT_COUNT, &convex_pts, &convex_pnt_cnt);

    EXPECT_TRUE(is_successful);

    expect_equal_arrays(convex_pts, CIRCLE_CONVEX_POINTS, CIRCLE_POINT_COUNT);
}
