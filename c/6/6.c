#include <stdio.h>
#include <math.h>
#include <locale.h>
#define N 20

int main()
{
	setlocale(LC_ALL, "Rus");
	int A[N] = { 0 };
	int SX = 0;
	int shift = 3;
	if (shift >= N) {
		shift %= N;
	}
	for (int i = 0; i < N; i++) {
		A[i] = i + 10;
		printf("%3d", A[i]);
	}
	printf("\n");
	while (SX != shift) {
		int tmp_t6 = A[N - 1];
		for (int i = N - 1; i > 0; --i) {
			A[i] = A[i - 1];
		}
		A[0] = tmp_t6;
		SX++;
	}
	for (int i = 0; i < N; i++) {
		printf("%3d", A[i]);
	}
	return 0;
}
