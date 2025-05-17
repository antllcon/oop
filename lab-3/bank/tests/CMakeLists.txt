cmake_minimum_required(VERSION 3.10)
project(MyBank)
find_package(GTest REQUIRED)
add_executable(unit-test main.cpp     ../class-person/person.cpp
    ../class-person-with-account/person-with-account.cpp
    ../class-bank/bank.cpp
    ../class-contact/contact-list.cpp unit-test.cpp)
target_link_libraries(unit-test GTest::gtest GTest::gtest_main)