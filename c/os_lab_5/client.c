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
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int recv_bytes;

    // Создание сокета
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Настройка параметров сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(PORT);

    // Подключение к серверу
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Ошибка при подключении к серверу");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Подключение к серверу прошло успешно\n");

    while (1) {
        // Ввод строки с клавиатуры
        printf("Введите строку для отправки: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Отправка данных серверу
        send(client_socket, buffer, strlen(buffer), 0);

        // Получение ответа от сервера
        recv_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
        if (recv_bytes > 0) {
            buffer[recv_bytes] = '\0';

            // Создание и запись в лог-файл клиента
            FILE* client_log = fopen("./temp/client1.log", "a");
            if (client_log != NULL) {
                fprintf(client_log, "Отправлено серверу: %s\n", buffer);
                fprintf(client_log, "Полуено от сервера: %s\n", buffer);
            } else {
                perror("Ошибка при открытии файла логов");
            }

            // Получение второго сообщения от сервера
            recv_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
            if (recv_bytes > 0) {
                buffer[recv_bytes] = '\0';

                if (client_log != NULL) {
                    fprintf(client_log, "Получено второе сообщение от сервера: %s\n", buffer);
                    fclose(client_log);
                }
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }

    // Закрытие сокета
    close(client_socket);

    return 0;
}