#include <stdio.h>
#include <math.h>
#include <locale.h>
#define NH 5
#define NW 10

int main()
{
	setlocale(LC_ALL, "Rus");
	int A[NH][NW];
	int stime;
	long ltime;
	ltime = time(0);
	stime = (unsigned)ltime / 2;
	srand(stime);

	for (int i = 0; i < NH; i++) {
		for (int j = 0; j < NW; j++) {
			A[i][j] = rand() % 100;
			printf("%2d ", A[i][j]);
		}

		printf("\n");
	}
	printf("\n");
	int maxI;
	int maxJ;
	int i, j;
	maxI = 0;
	maxJ = 0;
	for (i = 1; i < NH; i++) {

		for (j = 1; j < NW; j++) {

			if (A[i][j] > A[maxI][maxJ]) {
				maxI = i;
				maxJ = j;
			}
		}

	}

	printf("Максимальное значение массива = %d", A[maxI][maxJ]);
	return 0;
}
