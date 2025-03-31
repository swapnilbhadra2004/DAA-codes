#include <stdio.h>
#include <stdlib.h>
#define INF 10000

typedef struct {
    int x, y;
} Point;

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

void jarvisMarch(Point points[], int n) {
    if (n < 3) return;
    int hull[n], count = 0;
    int leftmost = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[leftmost].x)
            leftmost = i;
    
    int p = leftmost, q;
    do {
        hull[count++] = p;
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        p = q;
    } while (p != leftmost);
    
    printf("Convex Hull: \n");
    for (int i = 0; i < count; i++)
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
}

int main() {
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);
    jarvisMarch(points, n);
    return 0;
}
