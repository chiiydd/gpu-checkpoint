cmake_minimum_required(VERSION 3.5.0)
project(gpu-checkpoint VERSION 0.1.0 LANGUAGES C CXX)

option(USE_CUDA "Compile gpu-proxy with CUDA support" ON)

add_subdirectory(src/hijacker)

add_subdirectory(test)