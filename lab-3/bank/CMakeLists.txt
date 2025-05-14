cmake_minimum_required(VERSION 3.10)
project(MyBank)

file(GLOB SOURCES
  class-person/*.cpp
  class-person-with-account/*.cpp
  class-contact/*.cpp
  class-bank/*.cpp
  class-simulation/*.cpp
  class-homer/*.cpp
  class-marge/*.cpp
  class-lisa/*.cpp
  class-bart/*.cpp
  class-apu/*.cpp
  class-berns/*.cpp
  )

add_executable(start ${SOURCES} main.cpp)