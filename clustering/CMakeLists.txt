# cmake_minimum_required(VERSION <specify CMake version here>)
project(clustering)

set(CMAKE_CXX_STANDARD 17)

add_executable(clustering main.cpp csv.h datagen.h datagen.cpp csv.cpp dbscan.cpp dbscan.h kmeans.cpp kmeans.h)