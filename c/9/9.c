#include <stdio.h>
#include <math.h>
#include <locale.h>
#define N 10

int main()
{
	setlocale(LC_ALL, "Rus");
	int A[N];
	int max, tmp, i;
	for (i = 0; i < N; i++) {
		A[i] = i;
		printf("%3d", A[i]);
	}
	printf("\n");
	for (int i = 0; i < N; ++i) {
		max = i;
		for (int j = i + 1; j < N; j++) {
			if (A[j] > A[max]) {
				max = j;
			}
		}
		if (max != i) {
			tmp = A[i];
			A[i] = A[max];
			A[max] = tmp;
		}
	}
	for (i = 0; i < N; i++) {
		printf("%3d", A[i]);
	}
	return 0;
}
