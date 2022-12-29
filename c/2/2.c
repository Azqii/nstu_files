#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	printf("Введите коэффициенты квадратного уравнения\n");
	int coef_A, coef_B, coef_C;
	printf("a = ");
	scanf_s("%d", &coef_A);
	printf("b = ");
	scanf_s("%d", &coef_B);
	printf("c = ");
	scanf_s("%d", &coef_C);

	int x1, x2;
	if (coef_C == 0) {
		printf("Уравнение не квадратное\n");
		return 0;
	}

	else if (coef_B == 0) {
		printf("Уравнение не квадратное\n");
		return 0;
	}
	else if (coef_A == 0) {
		printf("Уравнение не квадратное\n");
		return 0;
	}
	else {
		long D;
		printf("%dx^2 + %dx + %d = 0\n", coef_A, coef_B, coef_C);
		D = pow(coef_B, 2) - (4 * coef_A * coef_C);
		if (D < 0) {
			printf("D %d < 0.\n", D);
			printf("У уравнения нет корней\n");
			return 0;
		}
		else if (D == 0) {
			x1 = -1 * coef_B / (2 * coef_A);
			printf("D = %d\n", D);
			printf("x1 = %d.\n\n", x1);
			return 0;
		}
		x1 = (-1 * coef_B - sqrt(D)) / (2 * coef_A);
		x2 = (-1 * coef_B + sqrt(D)) / (2 * coef_A);
		printf("D = %d\n", D);
		printf("x1 = %d, x2 = %d.\n\n", x1, x2);
	}
	return 0;
}
