file(GLOB GPU_PROXY_SRC_FILES *.cpp *.cu )
if (USE_CUDA)
    message(STATUS "Compiling GPU PROXY with CUDA")
    include_directories(${CMAKE_SOURCE_DIR}/include/common/cuda)
    include_directories(${CMAKE_SOURCE_DIR}/include/gpu-proxy/cuda)
    file(GLOB GPU_PROXY_CUDA_SRC_FILES cuda/*.cpp cuda/*.cu)
    
    add_executable(gpu-proxy 
                                ${GPU_PROXY_CUDA_SRC_FILES}
                                ${GPU_PROXY_SRC_FILES})
    set_target_properties(gpu-proxy PROPERTIES CUDA_ARCHITECTURES "75")
    target_compile_options(gpu-proxy PUBLIC -g -rdynamic )    
    target_link_libraries(gpu-proxy PUBLIC -lcuda)

endif()