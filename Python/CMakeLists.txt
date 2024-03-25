cmake_minimum_required(VERSION 3.16.0)

project(dsm VERSION 1.2.1 LANGUAGES CXX)

# Find the required packages
find_package(pybind11 REQUIRED)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the C++ flags
string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -g")

include_directories(../src/dsm/)

# Set the folder for the executable
# set(EXECUTABLE_OUTPUT_PATH ../)

# Define the executable
pybind11_add_module(Node binding.cpp)
