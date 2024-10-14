



if (USE_CUDA)
    message(STATUS "Compiling hijacker with CUDA")
    include_directories(${CMAKE_SOURCE_DIR}/include/hijacker/cuda)
    include_directories(${CMAKE_SOURCE_DIR}/include/common/cuda)
    file(GLOB HIJACK_CUDA_SRC_FILES cuda/*.cpp cuda/*.cu)
    set(HIJACKER_COMPILE_FLAGS -shared -fPIC -g -rdynamic -D_GNU_SOURCE -Wall)
    
    add_library(hijacker SHARED ${HIJACK_CUDA_SRC_FILES})
    target_compile_options(hijacker PUBLIC ${HIJACKER_COMPILE_FLAGS})
    target_link_libraries(hijacker PUBLIC -lcuda)
endif()


