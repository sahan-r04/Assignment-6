/*
 * Exercise VI - Question 3(a)(i)
 * Euclidean distance between two 2D points.
 *
 * The Euclidean distance is the "straight line" distance between two
 * points, given by the Pythagorean formula:
 *     d = sqrt( (x2 - x1)^2 + (y2 - y1)^2 )
 */

#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double euclideanDistance(Point p1, Point p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

int main(void) {
    Point p1, p2;

    printf("Enter coordinates of point 1 (x y): ");
    scanf("%lf %lf", &p1.x, &p1.y);

    printf("Enter coordinates of point 2 (x y): ");
    scanf("%lf %lf", &p2.x, &p2.y);

    double distance = euclideanDistance(p1, p2);
    printf("Euclidean distance = %.4f\n", distance);

    return 0;
}
