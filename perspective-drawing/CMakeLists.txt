cmake_minimum_required(VERSION 4.1)
project(perspective_drawing C)

execute_process(
        COMMAND brew --prefix sdl2
        OUTPUT_VARIABLE SDL2_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_C_STANDARD 11)

add_executable(perspective_drawing main.c
        point_list.c
        point_list.h)

target_include_directories(perspective_drawing PRIVATE
        ${SDL2_PREFIX}/include/SDL2
)

target_link_directories(perspective_drawing PRIVATE
        ${SDL2_PREFIX}/lib
)

target_link_libraries(perspective_drawing PRIVATE
        SDL2
)
