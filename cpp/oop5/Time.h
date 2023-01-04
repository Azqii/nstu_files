//
// Created by dima on 03.01.23.
//

#ifndef OOP5_TIME_H
#define OOP5_TIME_H

#include "DateTime.h"

class Time : public DateTime {
private:
    std::string timeAsString; // Поле строкового представления времени

private:
    void setTimeAsString(); // Сеттер для поля строкового представления времени

public:
    Time(int year, int month, int day, int hour, int minute); // Конструктор с параметрами

    Time(); // Конструктор по умолчанию

    Time(const Time &other); // Конструктор копирования

    void changeTime(int hours, int minutes); // Метод для изменения времени

    void printTime(); // Метод для вывода времени

    void plusHour() override; // Прибавляет 1 час.

    void minusHour() override; // Отнимает 1 час.

    void plusMinute() override; // Прибавляет 1 минуту.

    void minusMinute() override; // Отнимает 1 минуту.

    operator char *() override; // Преобразование к типу char*
};


#endif //OOP5_TIME_H
