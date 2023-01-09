#include "DateTime.h"


void testDateTime(){
    // Инициализация объекта класса DateTime
    DateTime first_date, second_date, third_date;

    // Ввод данных с помощью потока ввода
    std::cout << "Введите через пробел год, месяц, день, час и минуту для записи в текстовый файл:" << std::endl;
    std::cin >> first_date;

    std::fstream file; // Инициализация объекта для работы с файлами

    // Запись объекта в текстовый файл с помощью потока вывода
    file.open("./file.txt", std::fstream::out);
    if (file.is_open()) {
        file << first_date;
        file.close();
    } else {
        std::cout << "Файл не открыт" << std::endl;
    }

    // Считывание объекта из текстового файла с помощью потока ввода
    file.open("./file.txt", std::fstream::in);
    if (file.is_open()) {
        file >> second_date;
        file.close();
    } else {
        std::cout << "Файл не открыт" << std::endl;
    }

    // Вывод данных с помощью потока вывода
    std::cout << "Дата, полученная из текстового файла:" << " " << second_date << std::endl << std::endl;


    // Ввод данных с помощью потока ввода
    std::cout << "Введите через пробел год, месяц, день, час и минуту для записи в бинарный файл:" << std::endl;
    std::cin >> first_date;

    // Запись объекта в бинарный файл
    file.open("./file.bin", std::fstream::out | std::ios::binary);
    if (file.is_open()) {
        file.write((char*) &first_date, sizeof(DateTime));
        file.close();
    } else {
        std::cout << "Файл не открыт" << std::endl;
    }

    // Считывание объекта из бинарного файла
    file.open("./file.bin", std::fstream::in | std::ios::binary);
    if (file.is_open()) {
        file.read((char*) &third_date, sizeof(DateTime));
        file.close();
    } else {
        std::cout<< "Файл не открыт" << std::endl;
    }

    // Вывод данных с помощью потока вывода
    std::cout << "Дата, полученная из бинарного файла:" << " " << third_date << std::endl;
}

int main() {
    testDateTime(); // Вызов тестирующей функции
    return 0;
}
