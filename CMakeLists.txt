cmake_minimum_required(VERSION 3.3)
project(redirectflux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        ring.c
        )
add_executable(exe ${SOURCE_FILES})
