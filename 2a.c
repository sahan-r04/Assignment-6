/*
 * Exercise VI - Question 3(a)(ii)
 * Manhattan distance between two 2D points (the exercise sheet spells it
 * "Mantan Distance", which is a typo for "Manhattan Distance").
 *
 * The Manhattan distance is the sum of the absolute differences of the
 * coordinates - like walking along a city grid instead of flying straight:
 *     d = |x2 - x1| + |y2 - y1|
 */

#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double manhattanDistance(Point p1, Point p2) {
    return fabs(p2.x - p1.x) + fabs(p2.y - p1.y);
}

int main(void) {
    Point p1, p2;

    printf("Enter coordinates of point 1 (x y): ");
    scanf("%lf %lf", &p1.x, &p1.y);

    printf("Enter coordinates of point 2 (x y): ");
    scanf("%lf %lf", &p2.x, &p2.y);

    double distance = manhattanDistance(p1, p2);
    printf("Manhattan distance = %.4f\n", distance);

    return 0;
}
