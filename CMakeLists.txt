cmake_minimum_required(VERSION 3.9)
project(lem_in C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_C_STANDARD 99)
set(libft ${CMAKE_SOURCE_DIR}/libft/libft.a)

add_executable(lem_in main.c parse.c add_data.c handle_room.c verifer.c handle_link.c handle_neigh.c query.c handle_way.c print_ways.c handle_ants.c way_helpers.c)
target_link_libraries(lem_in ${libft})