#include <stdio.h>
#include <math.h>
#include <locale.h>
#define N 30

int main()
{
	setlocale(LC_ALL, "Rus");
	float A[N];
	double x = 0;
	int n;
	printf("Введите массив из 30 элементов\n");
	for (int i = 0; i < N; i++) {
		scanf_s("%d", &n);
		A[i] = n;
		x = x + A[i];
	}
	printf("Среднее арифметическое = %f\n", x / N);
	return 0;
}
