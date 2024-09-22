#include"cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"test_tool.c"
//cuda GPU���߳����൱�������ĸ��ÿ���̵߳������������ڶ�ռ�ù̶��ļĴ����͹����ڴ棬���cuda�����ڲ�ͬ�߳�֮���л���û�п����ģ�������Ҫ��CPU���߳��л������������ֳ��ָ��ֳ�


//��Ӳ���Ƕȿ���cuda�����Ҫע��ĵ�

//���߳����ǹ̶�32���̣߳����߳̿鲻��32����ʱ��������16����16���߳�Ҳ��Ϊһ���߳�����ռ��32���̵߳���Դ���Ĵ����ȣ�;

//����Ϊһ���߳�����SIMT���߳���������߳�ͬһʱ��ֻ��ִ����ͬ��ָ����˺������ڷ�֧���ʱ��
//���ܵ����߳����ֻ����߳���������ִ��ÿһ����֧����ͬһʱ���е�Ҫִ��if���е�Ҫִ��else����ʱֻ�ܰ�˳����ִ��if����ִ��else���߳�ֹͣ����ִ��else��ִ��if���߳�ֹͣ���⽫������������;

//��SM�еļĴ����͹����ڴ������ǹ̶��ģ�����˺���(��һ���߳�)ʹ�õļĴ���Խ�٣�����SM�ϲ��е��߳̿��Խ��;

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
//	printf("cuda memcpy����ʱ��: %f ��\n", time_taken_memcpy);
//	double time_taken_cuda = (double)(end_cuda - start_cuda) / CLOCKS_PER_SEC;
//	printf("cuda����ʱ��: %f ��\n", time_taken_cuda);
//	double time_taken_host = (double)(end_host - start_host) / CLOCKS_PER_SEC;
//	printf("host����ʱ��: %f ��\n", time_taken_host);
//	printf("cuda���ٱ�: %f\n", time_taken_host / (time_taken_memcpy * 2 + time_taken_cuda));
//
//	free(A);
//	free(B);
//	free(C);
//	free(C_GPU);
//	cudaDeviceReset();
//	return 0;
//}