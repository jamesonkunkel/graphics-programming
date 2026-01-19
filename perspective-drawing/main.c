#include <stdio.h>
#include <stdlib.h>

#include "point_list.h"

typedef struct NDC {
    double x, y;
} NDC;

/**
 * Tranform the 3D points in a PointList to normalized device coordinates
 * These are values between 0 and 1 that can be rendered on any display
 */
void transform_to_ndc(const PointList *in, NDC *out) {
    if (!out) {
        exit(1);
    }

    for (int i = 0; i < in->len; i++) {
        NDC point;

        point.x = in->points[i].x / in->points[i].z;
        point.y = in->points[i].y / in->points[i].z;
        out[i] = point;
    }
}

int main(void) {
    PointList list = init_points();

    add_point_to_list(&list, P(1, 2, 3));
    add_point_to_list(&list, P(1, 2, 3));

    print_point_list(&list);

    NDC *ndc_list = malloc(list.len * sizeof(NDC));
    transform_to_ndc(&list, ndc_list);

    printf("List of NDC:\n");
    for (int i = 0; i < list.len; i++) {
        printf("Point %d: %f %f\n", i, ndc_list[i].x, ndc_list[i].y);
    }

    free(ndc_list);

    free_point_list(&list);

    return 0;
}
