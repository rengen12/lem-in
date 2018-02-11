cmake_minimum_required(VERSION 3.9)
project(lem_in C)

set(CMAKE_C_STANDARD 99)
set(libft ${CMAKE_SOURCE_DIR}/libft/libft.a)

add_executable(lem_in main.c)
target_link_libraries(lem_in ${libft})