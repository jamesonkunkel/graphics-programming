#include <SDL.h>

#include "point_list.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

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

        const double z = in->points[i].z;

        if (z == 0) {
            out[i] = (NDC){0, 0};
            continue;
        }

        point.x = in->points[i].x / -z;
        point.y = in->points[i].y / -z;

        // normalize between 0 and 1, these can be multiplied by screen dimensions
        point.x = (point.x + 1) / 2;
        point.y = (point.y + 1) / 2;

        out[i] = point;
    }
}

void render_ndc(SDL_Renderer *ren, const NDC *ndc_list, const int len) {
    if (!ndc_list) {
        fprintf(stderr, "render_ndc: ndc_list is NULL\n");
        return;
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    for (int i = 0; i < len; i++) {
        const float x_trans = (float) ndc_list[i].x * SCREEN_WIDTH;
        const float y_trans = (float) ndc_list[i].y * SCREEN_HEIGHT;

        SDL_RenderDrawPointF(ren, x_trans, y_trans);
    }
}

int main(void) {
    PointList list = init_points();

    add_point_to_list(&list, P(0, 0, -1));
    add_point_to_list(&list, P(0.5, 0, -1));
    add_point_to_list(&list, P(0, 0.5, -1));
    add_point_to_list(&list, P(0.5, 0.5, -1));

    add_point_to_list(&list, P(0, 0, -3));
    add_point_to_list(&list, P(0.5, 0, -3));
    add_point_to_list(&list, P(0, 0.5, -3));
    add_point_to_list(&list, P(0.5, 0.5, -3));

    print_point_list(&list);

    NDC *ndc_list = malloc(list.len * sizeof(NDC));
    transform_to_ndc(&list, ndc_list);

    printf("List of NDC:\n");
    for (int i = 0; i < list.len; i++) {
        printf("Point %d: %f %f\n", i, ndc_list[i].x, ndc_list[i].y);
    }

    SDL_Window *window = SDL_CreateWindow(
        "SDL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        render_ndc(renderer, ndc_list, list.len);
        SDL_RenderPresent(renderer); // show what you drew

        SDL_Delay(16);
    }

    free(ndc_list);
    free_point_list(&list);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
