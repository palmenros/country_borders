cmake_minimum_required(VERSION 3.21)
project(frontieres C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(frontieres random_tester.c polygone.c frontieres.c)
target_link_libraries(frontieres m)