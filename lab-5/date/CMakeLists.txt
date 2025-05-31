cmake_minimum_required(VERSION 3.12)

# Название проекта
project(MyDate)

# Стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Исходные файлы
add_executable(start
        main.cpp
        Date/Date.cpp
)

# Директории с заголовочными файлами
target_include_directories(start PRIVATE
        ${CMAKE_SOURCE_DIR}/Date

)

enable_testing()
find_package(GTest REQUIRED)

add_executable(unit_tests
    test/main.cpp
    test/unit-test.cpp
    Date/Date.cpp
)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/Date
)

target_link_libraries(unit_tests PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME AllTests COMMAND unit_tests)