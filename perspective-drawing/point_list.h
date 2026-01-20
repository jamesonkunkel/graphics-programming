//
// Created by Jameson Kunkel on 1/18/26.
//

#ifndef PERSPECTIVE_DRAWING_POINT_LIST_H
#define PERSPECTIVE_DRAWING_POINT_LIST_H

// right now x grows from left to right, y grows from top to bottom and z grows toward the user perspective
typedef struct Point {
    double x, y, z;
} Point;

typedef struct PointList {
    Point *points;
    int len;
    int cap;
} PointList;

PointList init_points();

void free_point_list(PointList *list);

Point P(double x, double y, double z);

void add_point_to_list(PointList *list, Point point);

void print_point_list(const PointList *list);

#endif //PERSPECTIVE_DRAWING_POINT_LIST_H
