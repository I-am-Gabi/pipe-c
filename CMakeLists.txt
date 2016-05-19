cmake_minimum_required(VERSION 3.3)
project(redirectflux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

add_executable (
        tst_pipes

        src/tst_pipes.c
)

add_executable (
        tst_redirect

        src/tst_redirect.c
)

add_executable (
        station

        src/station.c
)

add_executable (
        ring

        src/ring.c
)