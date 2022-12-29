#include <stdio.h>
#include <math.h>
#include <locale.h>
#define N 20

int main()
{
	setlocale(LC_ALL, "Rus");
	int A[N] = { 0 };
	int i;
	for (i = 0; i < N; i++) {
		A[i] = i;
		printf("%3d", A[i]);
	}
	printf("\n");


	for (i = 0; i < N / 2; i++) {
		int tmp = A[i];
		A[i] = A[N - i - 1];
		A[N - i - 1] = tmp;
	}

	for (i = 0; i < N; i++) {
		printf("%3d", A[i]);
	}
	return 0;
}
