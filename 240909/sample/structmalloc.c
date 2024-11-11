#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

Point* createPoints(int n);
void inputPoints(Point* points, int n);
void printPoints(const Point* points, int n);
void freePoints(Point* points);

int main() {
    Point* points;
    int n;
    printf("Number of points: ");
    scanf("%d", &n);

    points = createPoints(n);
    if(points == NULL) {
        printf("Allocation failed\n");
        return -1;
    }
    inputPoints(points, n);
    printPoints(points, n);
    freePoints(points);
}

Point* createPoints(int n) {
    Point* point = (Point*)malloc(sizeof(Point)*n);
    return point;
}
void inputPoints(Point* points, int n) {
    for (int i = 0; i < n; i++) {
        printf("Point %d (x y): ", i + 1);
        scanf("%d %d", &points[i].x, &points[i].y); // Point*인데 왜 points[i].x ?
    }
}
void printPoints(const Point* points, int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }
}
void freePoints(Point* points) {
    free(points);
}