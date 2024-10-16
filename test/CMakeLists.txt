
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/common/cuda
    ${CMAKE_SOURCE_DIR}/include/hijacker/cuda
)
add_executable(test test.cpp)
target_link_libraries(test PRIVATE hijacker)
