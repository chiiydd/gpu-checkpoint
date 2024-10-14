



if (USE_CUDA)
    message(STATUS "Compiling hijacker with CUDA")
    include_directories(${CMAKE_SOURCE_DIR}/include/hijacker/cuda)
    include_directories(${CMAKE_SOURCE_DIR}/include/common/cuda)
    file(GLOB HIJACK_CUDA_SRC_FILES cuda/*.cpp cuda/*.cu)
    add_library(hijacker ${HIJACK_CUDA_SRC_FILES})
endif()


