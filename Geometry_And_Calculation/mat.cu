#include"cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"test_tool.c"
//cuda GPU的线程是相当轻量级的概念，每个线程的整个生命周期都占用固定的寄存器和共享内存，因此cuda核心在不同线程之间切换是没有开销的，即不需要像CPU的线程切换那样，保存现场恢复现场


//从硬件角度看，cuda编程需要注意的点

//①线程束是固定32个线程，当线程块不被32整除时，比如余16，这16个线程也作为一个线程束，占用32个线程的资源（寄存器等）;

//②因为一个线程束是SIMT，线程书的所有线程同一时间只能执行相同的指令，当核函数存在分支语句时，
//可能导致线程束分化，线程束将连续执行每一个分支，即同一时间有的要执行if，有的要执行else，此时只能按顺序先执行if，让执行else的线程停止，再执行else，执行if的线程停止，这将显著降低性能;

//③SM中的寄存器和共享内存数量是固定的，如果核函数(即一个线程)使用的寄存器越少，能在SM上并行的线程块就越多;

//


__global__ void mat_add(float* A, float* B, float* C, int N, int M) {
	unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;
	unsigned int index = x * M + y;
	if (x<N && y<M) {
		C[index] = A[index] + B[index];
	}
}

//int main() {
//	int N = 1024*16;
//	int M = 1024*16;
//	int Bytes = N * M * sizeof(float);
//	float* A = (float*)malloc(Bytes);
//	float* B = (float*)malloc(Bytes);
//	float* C = (float*)malloc(Bytes);
//	float* C_GPU = (float*)malloc(Bytes);
//	rand_init(A, N*M);
//	rand_init(B, N*M);
//
//	//device
//	cudaSetDevice(0);
//	float* d_A;
//	float* d_B;
//	float* d_C;
//	clock_t start_mem_cuda = clock();
//	cudaError_t status;
//	status = cudaMalloc<float>(&d_A, Bytes);
//	if (status != cudaSuccess) {
//		printf("CUDA error: %s\n", cudaGetErrorString(status));
//	}
//	status = cudaMalloc<float>(&d_B, Bytes);
//	if (status != cudaSuccess) {
//		printf("CUDA error: %s\n", cudaGetErrorString(status));
//	}
//	status = cudaMalloc<float>(&d_C, Bytes);
//	if (status != cudaSuccess) {
//		printf("CUDA error: %s\n", cudaGetErrorString(status));
//	}
//	status = cudaMemcpy(d_A, A, Bytes, cudaMemcpyHostToDevice);
//	if (status != cudaSuccess) {
//		printf("CUDA error: %s\n", cudaGetErrorString(status));
//	}
//	status = cudaMemcpy(d_B, B, Bytes, cudaMemcpyHostToDevice);
//	if (status != cudaSuccess) {
//		printf("CUDA error: %s\n", cudaGetErrorString(status));
//	}
//	clock_t end_mem_cuda = clock();
//	int x = 32;
//	int y = 32;
//	dim3 block(x, y);
//	dim3 grid((N + block.x - 1) / block.x, (M + block.y - 1) / block.y);
//	clock_t start_cuda = clock();
//	mat_add <<< grid, block >>> (d_A, d_B, d_C, N, M);
//	cudaDeviceSynchronize();
//	cudaMemcpy(C_GPU, d_C, Bytes, cudaMemcpyDeviceToHost);
//	clock_t end_cuda = clock();
//	cudaFree(d_A);
//	cudaFree(d_B);
//	cudaFree(d_C);
//
//	//host
//	clock_t start_host = clock();
//	int in = 0;
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < M; j++) {
//			int index = in + j;
//			C[index] = A[index] + B[index];
//		}
//		in += M;
//	}
//	clock_t end_host = clock();
//
//	check_acc(C, C_GPU, N);
//	double time_taken_memcpy = (double)(end_mem_cuda - start_mem_cuda) / CLOCKS_PER_SEC;
//	printf("cuda memcpy运行时间: %f 秒\n", time_taken_memcpy);
//	double time_taken_cuda = (double)(end_cuda - start_cuda) / CLOCKS_PER_SEC;
//	printf("cuda运行时间: %f 秒\n", time_taken_cuda);
//	double time_taken_host = (double)(end_host - start_host) / CLOCKS_PER_SEC;
//	printf("host运行时间: %f 秒\n", time_taken_host);
//	printf("cuda加速比: %f\n", time_taken_host / (time_taken_memcpy * 2 + time_taken_cuda));
//
//	free(A);
//	free(B);
//	free(C);
//	free(C_GPU);
//	cudaDeviceReset();
//	return 0;
//}