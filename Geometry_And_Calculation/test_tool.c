#include<stdlib.h>
#include<time.h>
void rand_init(float* h, int size) {
	float min = 1.0;
	float max = 5.0;
	srand((unsigned int)time(NULL));  // 设置随机数种子
	for (int i = 0; i < size; i++) {
		h[i] = min + (float)rand() / (float)RAND_MAX * (max - min);
	}
}

void check_acc(float* C, float* C_GPU, const int N) {
	float eps = 1e-65;
	bool match = true;
	for (int i = 0; i < N; i++) {
		if (C[i] - C_GPU[i] > eps) {
			printf("%d : %f - %f\n", i, C[i], C_GPU[i]);
			match = false;
			break;
		}
	}
	if (match)
		printf("acc ok\n");
	else
		printf("err > 1e-65\n");
}