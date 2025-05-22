cmake_minimum_required(VERSION 3.10)
project(MyShape)
find_package(GTest REQUIRED)
add_executable(unit-test main.cpp  
    ../Shape/BaseShape.cpp
    ../Shape/BaseSolidShape.cpp
    ../Shape/Point.cpp
    ../Shape/Circle.cpp
    ../Shape/Triangle.cpp
    ../Shape/Rectangle.cpp
    ../Shape/Line.cpp
    unit-test.cpp)
target_link_libraries(unit-test GTest::gtest GTest::gtest_main)