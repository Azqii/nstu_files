//
// Created by dima on 28.12.22.
//

#ifndef CPP_LAB1_DATETIME_H
#define CPP_LAB1_DATETIME_H

#include <iostream>

class DateTime {
private:
    int year, // Год
        month, // Месяц
        day, // День
        hour, // Час
        minute; // Минута

    // Поле с динамическим выделением памяти для хранения чисел месяца, введенного при инициализации объекта.
    // При использовании конструктора без параметров хранит в себе число 0.
    // Сделано исключительно в учебных целях, поле с практической пользой для данного класса я придумать не смог.
    int *days;

    std::string dateAsString; // Строковое представление даты

    static int objectsCounter; // Статический счетчик существующих объектов

private:
    void setDateAsString();

    void setYear(int value);

    void setMonth(int value);

    void setDay(int value);

    void setHour(int value);

    void setMinute(int value);

    static int daysInMonth(int monthNumber, int yearNumber);

public:
    DateTime(int year, int month, int day, int hour, int minute);

    DateTime();

    DateTime(const DateTime &other);

    ~DateTime();

    void plusYear();

    void minusYear();

    void plusMonth();

    void minusMonth();

    void plusDay();

    void minusDay();

    void plusHour();

    void minusHour();

    void plusMinute();

    void minusMinute();

    void printDateTime();

    static int getObjectsCounter();
};


#endif //CPP_LAB1_DATETIME_H
