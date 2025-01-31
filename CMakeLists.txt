cmake_minimum_required(VERSION 3.21)
project(pictures2)

set(CMAKE_CXX_STANDARD 14)

add_executable(pictures2 main.cpp camera.h color.h hittable.h hittable_list.h material.h ray.h rtweekend.h sphere.h vec3.h ellipsoid.h)
