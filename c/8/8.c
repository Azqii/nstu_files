#include <stdio.h>
#include <math.h>
#include <locale.h>
#define N 10

int main()
{
	setlocale(LC_ALL, "Rus");
	int A[N] = { 0 };
	int i, tmp, j, x=0;
	for (i = 0; i < N; i++) {
		A[i] = i;
		printf("%3d", A[i]);
	}
	printf("\n");
	while (x < N) {
		for (j = 1; j < N; j++)
			if (A[j] >= A[j - 1]) {
				tmp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = tmp;
			}
		x++;
	}
	for (i = 0; i < N; i++) {
		printf("%3d", A[i]);
	}
	printf("\n");
	return 0;
}
