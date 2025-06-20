cmake_minimum_required(VERSION 3.12)
project(HttpUrl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(start
    main.cpp
    ParseUrl.cpp
    Protocol.cpp
        HttpUrl.cpp 
)

add_executable(tests
    tests/main.cpp
    tests/UnitTests.cpp
    ParseUrl.cpp
    Protocol.cpp     
    HttpUrl.cpp   
)

find_package(fmt REQUIRED)
target_link_libraries(start PRIVATE fmt::fmt)
target_link_libraries(tests PRIVATE fmt::fmt)

enable_testing()
find_package(GTest REQUIRED)

target_include_directories(tests PRIVATE .)
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME AllTests COMMAND tests)