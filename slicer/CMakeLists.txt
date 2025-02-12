cmake_minimum_required(VERSION 3.26)

project(slicer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(cgal REQUIRED)

add_executable(slicer main.cpp)
target_link_libraries(slicer CGAL::CGAL)
