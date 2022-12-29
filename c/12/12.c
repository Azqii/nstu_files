#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int x1, x2, x3, y1, y2, y3;
	printf("Введите координаты трех точек на плоскости:\n");
	printf("x1, y1 = ");
	scanf_s("%d %d", &x1, &y1);
	printf("x2, y2 = ");
	scanf_s("%d %d", &x2, &y2);
	printf("x3, y3 = ");
	scanf_s("%d %d", &x3, &y3);
	if ((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3) == 0)
		printf("На этих координатах нельзя построить треугольник\n");
	else
		printf("На этих координатах можно построить треугольник\n");
	return 0;
}
