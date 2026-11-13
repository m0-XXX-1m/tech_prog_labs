cmake_minimum_required(VERSION 3.5)

project(lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

file(GLOB SOURCES "methods/*.cpp")
file(GLOB HEADERS "headers/*.h")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer")

add_executable(
    ${PROJECT_NAME}
    main.cpp
    ${SOURCES}
    ${HEADERS}
)