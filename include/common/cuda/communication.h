#include <cstddef>
enum cuda_call{
    CudaMalloc,
    CudaFree,
    CudaLaunchKernel,
    CudaMemcpy,
};


typedef struct {
    cuda_call op;

    union{
        struct{
            void **devPtr;
            size_t size;
        }cudaMalloc;

        struct{
            void *devPtr;
        }cudaFree;
        
        struct{
            const void *func;
            dim3 gridDim;
            dim3 blockDim;
            void **args;
            size_t sharedMem;
            cudaStream_t stream;
        }cudaLaunchKernel;
        struct{
            void *dst;
            const void *src;
            size_t count;
            enum cudaMemcpyKind kind;
        }cudaMemcpy;
    }params;
}cudaCallStructure;