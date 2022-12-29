#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#define X 1
#define Y 0

int main()
{
	setlocale(LC_ALL, "Rus");
	printf("Введите текст с точкой в конце:\n");
	int a=0, b = 0, c;
	c = Y;
	while ((a = getchar()) != '.') {		
		if (a == ' ' or a == '\t' or a == '\n')
			c = Y;
		else if (c == Y) {
			c = X;
			++b;
		}
	}
	printf("Всего слов = %d", b);
	return 0;
}
