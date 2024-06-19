cmake_minimum_required(VERSION 3.21)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(MulTwoPlayer VERSION 1.0.1)

include_directories(src/serial_library/include)
link_directories(src/serial_library/src)

set(serial_SRCS src/serial_library/src/SerialPort.cpp src/serial_library/include/SerialPort.hpp)

add_library(serial ${serial_SRCS})
target_link_libraries(serial)

# Set up the mod binary
add_library(${PROJECT_NAME} SHARED
    src/main_better.cpp
    src/serial_library/src/SerialPort.cpp
    src/serial_library/include/SerialPort.hpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Set up dependencies, resources, link Geode
setup_geode_mod(${PROJECT_NAME})