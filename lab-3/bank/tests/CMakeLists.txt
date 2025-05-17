cmake_minimum_required(VERSION 3.10)
project(MyBank)
find_package(GTest REQUIRED)
add_executable(unit-test main.cpp     ../class-person/person.cpp
    ../class-person-with-account/person-with-account.cpp
    ../class-bank/bank.cpp
    ../class-simulation/simulation.cpp
    ../class-homer/homer.cpp
    ../class-marge/marge.cpp
    ../class-apu/apu.cpp
    ../class-berns/berns.cpp
    ../class-chester/chester.cpp
    ../class-waylon/waylon.cpp
    ../class-lisa/lisa.cpp
    ../class-bart/bart.cpp
    ../class-nelson/nelson.cpp
    ../class-contact/contact-list.cpp unit-test.cpp)
target_link_libraries(unit-test GTest::gtest GTest::gtest_main)