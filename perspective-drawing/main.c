#include "point_list.h"

int main(void) {
    PointList list = init_points();

    add_point_to_list(&list, P(1, 2, 3));
    add_point_to_list(&list, P(1, 2, 3));

    print_point_list(&list);

    free_point_list(&list);

    return 0;
}
