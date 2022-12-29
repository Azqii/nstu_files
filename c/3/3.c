#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int x, digit_3;
	printf("Введите целое число не более чем из 10 разрядов: ");
	scanf_s("%d", &x);
	if (x > 999999999) {
		printf("Введеное число имеет больше 10 разрядов.\n");
			return 0;
	}
	else {
		printf("Введите цифру: ");
		scanf_s("%d", &digit_3);
		while (x > 0) {
			if (x % 10 == digit_3) {
				printf("Данная цифра входит в число.\n\n ");
				return 0;
			}
			else if (x <= 9) {
				printf("Данная цифра не входит в число.\n\n ");
			}
			x /= 10;
		}
	}
	return 0;
}
