#include <stdio.h>
#include <math.h>
#include <locale.h>
#define N 10

int main()
{
	setlocale(LC_ALL, "Rus");
	float A[N];
	double x = 0;
	int n;
	printf("Введите массив из 10 элементов\n");
	for (int i = 0; i < N; i++) {
		scanf_s("%d", &n);
		A[i] = n;
		x = x + A[i];
	}
	printf("\n");
	for (int i = 0; i < N; i++) {
		if (A[i] < A[i + 1]) {
			printf("Массив НЕ упорядочен в порядке убывания.\n");
			return 0;
		}
		else if (i == N - 1)
			printf("Массив упорядочен в порядке убывания.\n");
	}
	return 0;
}
