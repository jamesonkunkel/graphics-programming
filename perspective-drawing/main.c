#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    double x, y, z;
} Point;

typedef struct PointList {
    Point *points;
    int len;
    int cap;
} PointList;

PointList init_points() {
    PointList list;
    list.len = 0;
    list.cap = 10;

    list.points = malloc(list.cap * sizeof(Point));

    return list;
}

// point helper constructor
Point P(const double x, const double y, const double z) {
    const Point p = {x, y, z};
    return p;
}

void add_point_to_list(PointList *list, const Point point) {
    if (list->len >= list->cap) {
        list->cap *= 2;

        void *ptr = realloc(list->points, list->cap * sizeof(Point));

        if (ptr == NULL) {
            exit(1);
        }
        list->points = ptr;
    }

    list->points[list->len] = point;
    list->len++;
}

void print_point_list(const PointList *list) {
    printf("List of points:\n");
    for (int i = 0; i < list->len; i++) {
        printf("Point %d: %f %f %f\n", i, list->points[i].x, list->points[i].y, list->points[i].z);
    }
}

void free_point_list(PointList *list) {
    free(list->points);
    list->points = NULL;
    list->len = 0;
    list->cap = 0;
}

int main(void) {
    PointList list = init_points();

    add_point_to_list(&list, P(1, 2, 3));
    add_point_to_list(&list, P(1, 2, 3));

    print_point_list(&list);

    free_point_list(&list);

    return 0;
}
