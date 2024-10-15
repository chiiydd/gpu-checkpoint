cmake_minimum_required(VERSION 3.5.0)
project(gpu-checkpoint VERSION 0.1.0 LANGUAGES C CXX)

option(USE_CUDA "Compile gpu-proxy with CUDA support" ON)
if (NOT DEFINED ENV{CUDA_HOME})
    set(CUDA_HOME /usr/local/cuda)
else()
    set(CUDA_HOME $ENV{CUDA_HOME})
endif()

include_directories(${CUDA_HOME}/include)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_subdirectory(src/hijacker)

add_subdirectory(test)