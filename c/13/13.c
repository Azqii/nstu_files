#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int a, b, c;
	printf("Введите длину стороны квадрата ");
	scanf_s("%d", &a);
	b = a / 2;
	c = a / sqrt(2);
	printf("Радиус вписанной окружности = %d\n", b);
	printf("Радиус описанной окружности =%d\n)", c);
	return 0;
}
