cmake_minimum_required(VERSION 3.10)
project(MyGoogleTest)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
endif()

find_package(GTest REQUIRED) 
add_executable(unit-test main.cpp ../prime.cpp unit-test.cpp)
target_link_libraries(unit-test GTest::gtest GTest::gtest_main)

target_compile_options(unit-test PRIVATE 
    $<$<CONFIG:Release>:-O3> 
)