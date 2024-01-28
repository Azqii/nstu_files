//
// Created by dima on 16.01.24.
//

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Неверное число аргументов");
        return 1;
    }

    const int remove_status = remove(argv[1]);
    if (remove_status != 0) {
        fprintf(stderr, "Не получилось удалить файл");
        return 1;
    }

    return 0;
}
