#include"cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
//#include"test_tool.c"


__global__ void vec_add(float* A, float* B, float* C, const int N, const int iter_time) {
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if(i<N)
		for (int k = 0; k < iter_time; k++) {
			C[i] += A[i] + B[i];
		}
}

//int main() {
//	//init memory
//	int iter_time = 20;
//	int N = 1024*1024*128;
//	int thNum = 1024;
//	int NBytes = N * sizeof(float);
//	float* A = (float*)malloc(NBytes);
//	float* B = (float*)malloc(NBytes);
//	float* C = (float*)malloc(NBytes);
//	float* C_GPU = (float*)malloc(NBytes);
//	memset(C, 0, N);
//	memset(C_GPU, 0, N);
//	rand_init(A, N);
//	rand_init(B, N);
//
//	//device
//	cudaSetDevice(0);
//	float* d_A;
//	float* d_B;
//	float* d_C;
//	clock_t start_mem_cuda = clock();
//	cudaMalloc<float>(&d_A, NBytes);
//	cudaMalloc<float>(&d_B, NBytes);
//	cudaMalloc<float>(&d_C, NBytes);
//	cudaMemcpy(d_A, A, NBytes, cudaMemcpyHostToDevice);
//	cudaMemcpy(d_B, B, NBytes, cudaMemcpyHostToDevice);
//	clock_t end_mem_cuda = clock();
//	dim3 block(thNum);
//	dim3 grid((N + block.x - 1) / block.x);
//	clock_t start_cuda = clock();
//	//block����( 1 <= block���� <= 65535)�� block���߳�������1<= �߳����� <= 1024��
//	vec_add << <grid, block >> > (d_A, d_B, d_C, N, iter_time);
//	cudaDeviceSynchronize();
//	clock_t end_cuda = clock();
//	//ע�⣺��һ�����������ݵ��յ㣬�ڶ������������ݵ���㡣����㿽�����յ㡣��Ϊ��Ҫ��deviec������host����������������յ���host�������device��
//	cudaMemcpy(C_GPU, d_C, NBytes, cudaMemcpyDeviceToHost);
//	cudaFree(d_A);
//	cudaFree(d_B);
//	cudaFree(d_C);
//
//	//host
//	clock_t start_host = clock();
//	for (int k = 0; k < iter_time; k++) {
//		for (int i = 0; i < N; i++) {
//			C[i] += A[i] + B[i];
//		}
//	}
//	clock_t end_host = clock();
//
//	//check and report
//	check_acc(C, C_GPU, N);
//	double time_taken_memcpy = (double)(end_mem_cuda - start_mem_cuda) / CLOCKS_PER_SEC;
//	printf("cuda memcpy����ʱ��: %f ��\n", time_taken_memcpy);
//	double time_taken_cuda = (double)(end_cuda - start_cuda) / CLOCKS_PER_SEC;
//	printf("cuda����ʱ��: %f ��\n", time_taken_cuda);
//	double time_taken_host = (double)(end_host - start_host) / CLOCKS_PER_SEC;
//	printf("host����ʱ��: %f ��\n", time_taken_host);
//	printf("cuda���ٱ�: %f\n", time_taken_host/(time_taken_memcpy * 2 + time_taken_cuda));
//
//	//free memory
//	free(A);
//	free(B);
//	free(C);
//	free(C_GPU);
//
//	return 0;
//}

