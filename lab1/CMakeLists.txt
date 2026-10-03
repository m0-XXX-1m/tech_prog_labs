cmake_minimum_required(VERSION 4.0)

project(keeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

file(GLOB SOURCES "methods/*.cpp")
file(GLOB HEADERS "headers/*.h")

add_executable(${PROJECT_NAME} main.cpp classes.h ${SOURCES} ${HEADERS})