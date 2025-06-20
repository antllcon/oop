
cmake_minimum_required(VERSION 3.12)
project(MyVector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(start
    main.cpp
)

add_executable(tests
    tests/main.cpp
    tests/UnitTests.cpp
)

enable_testing()
find_package(GTest REQUIRED)

target_include_directories(tests PRIVATE .)
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME AllTests COMMAND tests)