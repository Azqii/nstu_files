//
// Created by dima on 16.01.24.
//

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Неверное число аргументов");
        return 1;
    }

    FILE *file = fopen(argv[1], "w");
    fclose(file);

    return 0;
}
