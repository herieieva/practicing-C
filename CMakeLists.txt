cmake_minimum_required(VERSION 3.29)
project(practicing_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(practicing_C
        main.c
        practicing.c
        practicing.h)
