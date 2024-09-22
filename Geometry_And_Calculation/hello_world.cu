#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>


//__glogbal__指明是GPU上执行的代码，将采用nvcc进行编译
__global__ void helloFromGPU(void) {
	printf("threadId: %d,%d,%d ; blockId: %d,%d,%d ; blockDim: %d,%d,%d ; gridDim: %d,%d,%d\n",
		threadIdx.x, threadIdx.y, threadIdx.z, blockIdx.x, blockIdx.y, blockIdx.z, blockDim.x, blockDim.y, blockDim.z, gridDim.x, gridDim.y, gridDim.z);
}

//典型的cuda编程的五个步骤
//1.分配GPU内存
//2.从CPU内存拷贝数据到GPU内存
//3.调用cuda内核函数来完成运算
//4.将数据从GPU内存拷贝回CPU内存
//5.释放GPU内存

//int main(void) {
//	int nElem = 6;
//	dim3 block(3);
//	dim3 grid((nElem + block.x - 1) / 2);
//	helloFromGPU << <grid, block >> > ();
//	printf("hello world from CPU\n");
//	//显示的释放
//	//cudaDeviceReset();
//	cudaDeviceSynchronize();
//	return 0;
//}