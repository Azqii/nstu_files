//
// Created by dima on 04.01.23.
//

#ifndef OOP6_PLANNEDEVENT_H
#define OOP6_PLANNEDEVENT_H

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

    // Перегрузка оператора потока вывода
    friend std::ostream &operator<<(std::ostream &os, const PlannedEvent &plannedEvent);

    // Перегрузка оператора потока ввода
    friend std::istream &operator>>(std::istream &is, PlannedEvent &plannedEvent);

    operator char *() override; // Преобразование к типу char*
};


#endif //OOP6_PLANNEDEVENT_H