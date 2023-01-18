//
// Created by dima on 03.01.23.
//

#ifndef OOP4_PLANNEDEVENT_H
#define OOP4_PLANNEDEVENT_H

#include "DateTime.h"


class PlannedEvent : public DateTime {
private:
    std::string eventName; // Поле название мероприятия

public:
    PlannedEvent(int year, int month, int day, int hour, int minute,
                 std::string eventName); // Конструктор с параметрами

    PlannedEvent(); // Конструктор по умолчанию

    PlannedEvent(const PlannedEvent &other); // Конструктор копирования

    void setEventName(std::string value); // Сеттер поля названия мероприятия

    operator char *() override; // Преобразование к типу char*

    // Перегрузка оператора потока вывода
    friend std::ostream &operator<<(std::ostream &os, const PlannedEvent &plannedEvent);

    // Перегрузка оператора потока ввода
    friend std::istream &operator>>(std::istream &is, PlannedEvent &plannedEvent);

    // Перегрузка оператора потока вывода в файл
    friend std::fstream &operator<<(std::fstream &os, PlannedEvent &plannedEvent);
};


#endif //OOP4_PLANNEDEVENT_H
