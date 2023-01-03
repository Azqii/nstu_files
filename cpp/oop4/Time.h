//
// Created by dima on 03.01.23.
//

#ifndef OOP4_TIME_H
#define OOP4_TIME_H


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

    void plusHour(); // Прибавляет 1 час.

    void minusHour(); // Отнимает 1 час.

    void plusMinute(); // Прибавляет 1 минуту.

    void minusMinute(); // Отнимает 1 минуту.
};


#endif //OOP4_TIME_H
