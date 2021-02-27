cmake_minimum_required(VERSION 3.17)
project(lab1v2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab1v2 main.c daemonize.h daemonize.c)