cmake_minimum_required(VERSION 3.10)
project(MyPrime)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
add_executable(start main.cpp prime.cpp)