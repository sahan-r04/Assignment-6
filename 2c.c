/*
 * Exercise VI - Question 3(a)(iii)
 * Chebyshev distance between two 2D points.
 *
 * The Chebyshev distance is the greatest of the absolute differences
 * along each coordinate axis - like the minimum number of moves a king
 * needs on a chessboard:
 *     d = max( |x2 - x1| , |y2 - y1| )
 */

#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double chebyshevDistance(Point p1, Point p2) {
    double dx = fabs(p2.x - p1.x);
    double dy = fabs(p2.y - p1.y);
    return dx > dy ? dx : dy;
}

int main(void) {
    Point p1, p2;

    printf("Enter coordinates of point 1 (x y): ");
    scanf("%lf %lf", &p1.x, &p1.y);

    printf("Enter coordinates of point 2 (x y): ");
    scanf("%lf %lf", &p2.x, &p2.y);

    double distance = chebyshevDistance(p1, p2);
    printf("Chebyshev distance = %.4f\n", distance);

    return 0;
}
