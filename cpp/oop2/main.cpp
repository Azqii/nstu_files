#include "DateTime.h"

void testDateTime() {
    // Создание двух объектов класса с помощью конструктора с параметрами.
    DateTime first_date = DateTime(2020, 10, 29, 20, 30);
    DateTime second_date = DateTime(433, 3, 1, 0, 30);

    // Проверка правильности вывода данных
    std::cout << "Первая дата: ";
    first_date.printDateTime();
    std::cout << "Вторая дата: ";
    second_date.printDateTime();

    std::cout << "\n*******************************************************************************\n" << std::endl;

    // Тестирование перегруженных операторов сложения/вычитания
    DateTime plus = first_date + second_date;
    DateTime minus = first_date - second_date;
    std::cout << "Дата, полученная после сложения: ";
    plus.printDateTime();
    std::cout << "Дата, полученная после вычитания: ";
    minus.printDateTime();

    std::cout << "\n*******************************************************************************\n" << std::endl;

    // Тестирование перегруженного оператора присваивания
    DateTime assignment;
    assignment = first_date;
    std::cout << "Дата, полученная оператором присваивания из первой даты: ";
    assignment.printDateTime();

    std::cout << "\n*******************************************************************************\n" << std::endl;

    // Тестирование преобразования к типу char*
    char *testChar = first_date;
    std::cout << "Дата, полученная с помощью преобразования к типу char* первой даты: ";
    std::cout << testChar;
}

int main() {
    testDateTime(); // Вызов тестирующей функции
    return 0;
}
