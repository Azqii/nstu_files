#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Rus");
	printf("Введите 2-значное число\n");
	int x;
	scanf_s("%d", &x);
	printf("Ответ %d%d%d%d", x / 10, x / 10, x % 10, x % 10);
	return 0;
}