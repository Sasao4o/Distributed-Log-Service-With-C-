# Outer CMakeLists.txt

cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PROLOG C CXX)

# Include the CMakeLists.txt in src and tests
add_subdirectory(test)
add_subdirectory(src)

