cmake_minimum_required(VERSION 3.20)
project(philo_test C)

set(
        CMAKE_C_STANDARD 99
        philo.h
    )

include_directories(.)

add_executable(
        philo_test
        sources/main.c
        philo.h
        sources/utils.c sources/init.c)
