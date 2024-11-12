#include <cuda_runtime.h>
#include <iostream>

__global__ void add(int *dev_a, int *dev_b, int *dev_c) {
    dev_c[threadIdx.x] = dev_a[threadIdx.x] + dev_b[threadIdx.x];
}

int main(){
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {10, 20, 30, 40, 50};
    int c[5] = {0, 0, 0, 0, 0};

    int *dev_a, *dev_b, *dev_c;
    cudaMalloc((void**)&dev_a, 5 * sizeof(int));
    cudaMalloc((void**)&dev_b, 5 * sizeof(int));
    cudaMalloc((void**)&dev_c, 5 * sizeof(int));

    cudaMemcpy(dev_a, a, 5 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, 5 * sizeof(int), cudaMemcpyHostToDevice);

    add<<<1, 5>>>(dev_a, dev_b, dev_c);

    cudaMemcpy(c, dev_c, 5 * sizeof(int), cudaMemcpyDeviceToHost);

    for(int i = 0; i < 5; i++){
        std::cout << c[i] << std::endl;
    }

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

    return 0;
}