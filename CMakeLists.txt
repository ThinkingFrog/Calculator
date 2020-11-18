cmake_minimum_required(VERSION 3.10)
project(Calculator)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SRC src/*.cpp)

add_executable(Calculator ${SRC})
target_link_libraries(Calculator kernel32.dll)

add_library(division SHARED lib_src/Division.cpp)
add_library(power SHARED lib_src/Power.cpp)
add_library(cosinus SHARED lib_src/cosinus.cpp)
add_library(substraction SHARED lib_src/Substraction.cpp)
add_library(factorial SHARED lib_src/Factorial.cpp)