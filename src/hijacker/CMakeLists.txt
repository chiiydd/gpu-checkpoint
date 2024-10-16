


include_directories(${CMAKE_SOURCE_DIR}/include/hijacker)
file(GLOB HIJACK_SRC_FILES *.cpp )
if (USE_CUDA)
    message(STATUS "Compiling hijacker with CUDA")
    include_directories(${CMAKE_SOURCE_DIR}/include/common/cuda)
    include_directories(${CMAKE_SOURCE_DIR}/include/hijacker/cuda)
    file(GLOB HIJACK_CUDA_SRC_FILES cuda/*.cpp cuda/*.cu)
    set(HIJACKER_COMPILE_FLAGS -shared -fPIC -g -rdynamic -D_GNU_SOURCE -Wall)
    
    add_library(hijacker SHARED 
                                ${HIJACK_CUDA_SRC_FILES}
                                ${HIJACK_SRC_FILES})
    target_compile_options(hijacker PUBLIC ${HIJACKER_COMPILE_FLAGS})
    
endif()


