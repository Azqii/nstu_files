#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int putm(char*) {
    printf("Имитация работы с ресурсом\n");
    return 0;
}

int waitprocess(void) {
    printf("Имитация ожидания завершения другого процесса\n");
    return 0;
}

int main(int argc, char** argv) {
    key_t key;
    int shmid;
    char* shmaddr;

    if ((key = ftok("/tmp/ter", 'S')) == -1) {
        perror("Ошибка при генерации ключа\n");
        exit(EXIT_FAILURE);
    }
    printf("Ключ сгенерирован\n");

    if ((shmid = shmget(key, 100, 0666 | IPC_CREAT)) == -1) {
        perror("Ошибка при получении идентификатора\n");
        exit(EXIT_FAILURE);
    }
    printf("Идентификатор получен/создан\n");

    if ((shmaddr = shmat(shmid, NULL, 0)) == (char*)-1) {
        perror("Ошибка при подключении к разделяемой памяти\n");
        exit(EXIT_FAILURE);
    }
    printf("Подключение к разделяемой памяти прошло успешно\n");

    putm(shmaddr);
    waitprocess();

    if (shmdt(shmaddr) == -1) {
        perror("Ошибка при отключении от разделяемой памяти\n");
        exit(EXIT_FAILURE);
    }
    printf("Отключение от разделяемой памяти прошло успешно\n");

    if (shmctl(shmid,IPC_RMID, NULL) == -1) {
        perror("Ошибка уничтожения разделяемой памяти\n");
        exit(EXIT_FAILURE);
    }
    printf("Разделяемая память уничтожена");

    return 0;
}
