cmake_minimum_required(VERSION 3.10)
project(MyShape)

file(GLOB SOURCES
  Shape/*.cpp
  Canvas/*.cpp
  ShapeController/*.cpp
  )

add_executable(start ${SOURCES} main.cpp)

target_link_libraries(start sfml-graphics sfml-window sfml-system)