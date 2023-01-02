#include "DateTime.h"
#include <fstream>

void testDateTime(){
    // Инициализация объекта класса DateTime
    DateTime first_date, second_date;

    // Ввод данных с помощью потока ввода
    std::cout << "Введите через пробел год, месяц, день, час и минуту:" << std::endl;
    std::cin >> first_date;

    std::fstream file; // Инициализация объекта для работы с файлами

    // Запись объекта в файл с помощью потока вывода
    file.open("./file.txt", std::fstream::out);
    if (file.is_open()) {
        file << first_date;
        file.close();
    } else {
        std::cout << "Файл не открыт";
    }

    // Считывание объекта из файла с помощью потока ввода
    file.open("./file.txt", std::fstream::in);
    if (file.is_open()) {
        file >> second_date;
        file.close();
    } else {
        std::cout << "Файл не открыт";
    }

    // Вывод данных с помощью потока вывода
    std::cout << "Дата, полученная из файла:" << std::endl << second_date;
}

int main() {
    testDateTime(); // Вызов тестирующей функции
    return 0;
}
