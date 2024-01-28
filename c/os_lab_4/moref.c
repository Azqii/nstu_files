#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PAGE_SIZE 10

void displayFile(FILE *file, int pageSize) {
    int ch, lines = 0;

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);

        if (ch == '\n') {
            lines++;

            if (lines == pageSize) {
                lines = 0;
                printf("Нажмите Enter, чтобы продолжить");
                while (getchar() != '\n');  // Ожидание нажатия Enter
                printf("\n");
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int pageSize = DEFAULT_PAGE_SIZE;

    if (argc < 2) {
        fprintf(stderr, "Неверное число аргументов\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'n') {
            pageSize = atoi(argv[i] + 2);
            if (pageSize <= 0) {
                fprintf(stderr, "Длина порции не должна быть меньше 1\n");
                return 1;
            }
        } else {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "Ошибка при открытии файла\n");
                return 1;
            }

            displayFile(file, pageSize);

            fclose(file);
        }
    }

    return 0;
}
