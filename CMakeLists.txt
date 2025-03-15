cmake_minimum_required(VERSION 3.10)

project(sopp LANGUAGES CXX)

option(SOPP_BUILD_DEMO "Enable building the demo" OFF)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

# Set strict compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast")

# Create an interface library
add_library(sopp INTERFACE)

# Specify the include directory for consumers of the library
target_include_directories(sopp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Installation rules (optional, for distribution)
include(GNUInstallDirs)
install(TARGETS sopp EXPORT soppConfig)
install(EXPORT soppConfig DESTINATION ${CMAKE_INSTALL_DATADIR}/sopp)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Generate and install pkg-config file
set(PKG_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/sopp.pc")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sopp.pc.in ${PKG_CONFIG_FILE} @ONLY)
install(FILES ${PKG_CONFIG_FILE} DESTINATION ${CMAKE_INSTALL_DATADIR}/pkgconfig)

# Add demo directory (optional)
if (SOPP_BUILD_DEMO AND CMAKE_PROJECT_NAME STREQUAL "sopp")
    add_subdirectory(demo)
endif()
