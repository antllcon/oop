cmake_minimum_required(VERSION 3.12)
project(ParseUrl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(start
    main.cpp
    ParseUrl.cpp
)

enable_testing()
find_package(GTest REQUIRED)

add_executable(tests
    tests/main.cpp
    tests/unitTests.cpp
    ParseUrl.cpp
)

target_include_directories(tests PRIVATE .)
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME AllTests COMMAND tests)