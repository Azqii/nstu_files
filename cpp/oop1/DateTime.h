//
// Created by dima on 28.12.22.
//

#ifndef CPP_LAB1_DATETIME_H
#define CPP_LAB1_DATETIME_H

#include <iostream>

class DateTime {
private:
    int year, // Год.
        month, // Месяц.
        day, // День.
        hour, // Час.
        minute; // Минута.

    // Поле с динамическим выделением памяти для хранения чисел месяца, введенного при инициализации объекта.
    // При использовании конструктора без параметров хранит в себе число 0.
    // Сделано исключительно в учебных целях, поле с практической пользой для данного класса я придумать не смог.
    int *days;

    std::string dateAsString; // Строковое представление даты.

    static int objectsCounter; // Статический счетчик существующих объектов.

private:
    void setDateAsString(); // Сеттер для поля строкового представления даты.

    void setYear(int value); // Сеттер для поля года.

    void setMonth(int value); // Сеттер для поля месяца.

    void setDay(int value); // Сеттер для поля дня.

    void setHour(int value); // Сеттер для поля часа.

    void setMinute(int value); // Сеттер для поля минуты.

    static int daysInMonth(int monthNumber, int yearNumber); // Метод для определения количества дней в месяце.

public:
    DateTime(int year, int month, int day, int hour, int minute); // Конструктор с параметрами.

    DateTime(); // Конструктор по умолчанию (без параметров).

    DateTime(const DateTime &other); // Конструктор копирования.

    ~DateTime(); // Деструктор.

    void plusYear(); // Прибавляет 1 год.

    void minusYear(); // Отнимает 1 год.

    void plusMonth(); // Прибавляет 1 месяц.

    void minusMonth(); // Отнимает 1 месяц.

    void plusDay(); // Прибавляет 1 день.

    void minusDay(); // Отнимает 1 день.

    void plusHour(); // Прибавляет 1 час.

    void minusHour(); // Отнимает 1 час.

    void plusMinute(); // Прибавляет 1 минуту.

    void minusMinute(); // Отнимает 1 минуту.

    void printDateTime(); // Распечатывает время и дату.

    static int getObjectsCounter(); // Геттер счетчика объектов.
};


#endif //CPP_LAB1_DATETIME_H
