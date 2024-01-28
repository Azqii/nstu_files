#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char back_message[] = "iohqoidhasiodasjd";
    int recv_bytes;

    // Создание сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Ошибка при создании сокета");
        exit(1);
    }

    // Настройка параметров сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Привязка сокета к адресу и порту
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Ошибка при привязке сокета");
        close(server_socket);
        exit(1);
    }

    // Ожидание подключения клиента
    if (listen(server_socket, 1) == -1) {
        perror("Ошибка при ожидании подключения клиента");
        close(server_socket);
        exit(1);
    }

    printf("Сервер слушает на порту %d...\n", PORT);

    while (1) {
        // Принятие соединения от клиента
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            perror("Ошибка при принятии подключения от клиента");
            close(server_socket);
            exit(1);
        }

        printf("Клиент успешно подключен\n");

        while (1) {
            // Чтение данных от клиента
            recv_bytes = recv(client_socket, buffer, BUFFER_SIZE, 0);
            if (recv_bytes <= 0) {
                break;
            }

            buffer[recv_bytes] = '\0';
            printf("Получено от клиента: %s\n", buffer);

            // Отправка ответа клиенту
            send(client_socket, buffer, strlen(buffer), 0);
            printf("Отправлено клиенту: %s\n", buffer);

            // Создание и запись в лог-файл сервера
            FILE* server_log = fopen("./temp/server1.log", "a");
            if (server_log != NULL) {
                fprintf(server_log, "Полуечно от клиента: %s\n", buffer);
                fprintf(server_log, "Отправлено клиенту обратно: %s\n", buffer);
            }
            else {
                perror("Ошибка при открытии файла логов");
            }

            // Отправка второго сообщения клиенту
            send(client_socket, back_message, strlen(back_message), 0);
            printf("Еще отправлено клиенту: %s\n", back_message);

            // Дописываем второе сообщение в лог
            if (server_log != NULL) {
                fprintf(server_log, "Второе сообщение клиенту: %s\n", back_message);
                fclose(server_log);
            }
        }

        // Закрытие сокета клиента
        close(client_socket);
    }

    // Закрытие сокета клиента, но т.к. для выхода из цикла нет условия, то до сюда мы никогда не доберемся,
    // только через принудительное завершение программы, и тогда сокет еще какое-то время будет занимать порт.
    close(server_socket);

    return 0;
}
