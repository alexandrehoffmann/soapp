cmake_minimum_required(VERSION 3.10)

project(sopp_demo LANGUAGES CXX)

add_executable(demo_tuple demo_tuple.cpp)
add_executable(demo_array demo_array.cpp)

# Link the sopp library
target_link_libraries(demo_tuple PRIVATE sopp)
target_link_libraries(demo_array PRIVATE sopp)

# Specify include directories
target_include_directories(demo_tuple PRIVATE . ${CMAKE_SOURCE_DIR}/include)
target_include_directories(demo_array PRIVATE . ${CMAKE_SOURCE_DIR}/include)
