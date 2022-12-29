#include <stdio.h>
#include <math.h>
#include <locale.h>
#define NH 5
#define NW 5

int main()
{
	setlocale(LC_ALL, "Rus");
	int A[NH][NW], i ,j;
	printf("Введите двумерный массив 5х5\n");
	for (i = 0; i < NH; i++) {
		for (j = 0; j < NW-1; j++) {
			scanf_s(" %d ", &A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < NH; i++) {
		for (j = 0; j < NW; j++) {

			if (A[i][j] % 2 == 0) {
				A[i][j] = 0;
			}
			else
				A[i][j] = 1;
			if (i == j || i + j == 4)
				A[i][j] = 2;
			printf(" %d ", A[i][j]);
		}
		printf("\n");
	}
	return 0;
}
