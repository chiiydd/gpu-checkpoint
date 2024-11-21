
add_executable(test test.cu)
set_target_properties(test PROPERTIES CUDA_ARCHITECTURES "75")
<<<<<<< HEAD
=======

>>>>>>> hook_without_proxy
target_compile_options(test PUBLIC -g )

# target_link_libraries(test PUBLIC -lcuda)
