cmake_minimum_required(VERSION 3.10)

project(angle)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
file(GLOB SOURCES
    src/*.cpp
)

add_executable(angle ${SOURCES})
