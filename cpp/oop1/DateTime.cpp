//
// Created by dima on 28.12.22.
//

#include "DateTime.h"

int DateTime::objectsCounter = 0; // Присваивание значения статическому полю.

void DateTime::setYear(int value) {
    this->year = value;
}

void DateTime::setMonth(int value) {
    if (value < 1 or value > 12)
        throw std::invalid_argument("Такого месяца не существует");

    this->month = value;
}

int DateTime::daysInMonth(int monthNumber, int yearNumber) {
    switch (monthNumber) {
        case 0: // Для конструктора копирования объекта созданного конструктором по умолчанию.
            return 1;
        case 2:
            if (yearNumber % 4 == 0 && (yearNumber % 100 != 0 || yearNumber % 400 == 0)) // Проверка на високосный год
                return 29;
            else
                return 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

void DateTime::setDay(int value) {
    if (this->month == 0)
        throw std::logic_error("Сначала измените значение месяца");
    else if (value < 0 || value > this->daysInMonth(this->month, this->year))
        throw std::invalid_argument("В этом месяце нет такого дня");

    this->day = value;
}

void DateTime::setHour(int value) {
    if (value < 0 || value > 23)
        throw std::invalid_argument("Часы могут быть только в промежутке между 0 и 24");

    this->hour = value;
}

void DateTime::setMinute(int value) {
    if (value < 0 || value > 59)
        throw std::invalid_argument("Минуты могут быть только в промежутке между 0 и 60");

    this->minute = value;
}

void DateTime::setDateAsString() {
    this->dateAsString =
            std::to_string(this->day) + "." + std::to_string(this->month) + "." + std::to_string(this->year) + " " +
            std::to_string(this->hour) + ":" + std::to_string(this->minute);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute) {
    std::cout << "Вызван конструктор с параметрами для объекта в " << this << std::endl;

    this->setYear(year);
    this->setMonth(month);
    this->setDay(day);
    this->setHour(hour);
    this->setMinute(minute);

    this->setDateAsString();

    int daysSize = this->daysInMonth(this->month, this->year);
    this->days = new int[daysSize];
    for (int i = 0; i < daysSize; i++) {
        this->days[i] = i + 1;
    }

    DateTime::objectsCounter++;
}

DateTime::DateTime() {
    std::cout << "Вызван конструктор по умолчанию для объекта в " << this << std::endl;

    this->year = 0;
    this->month = 0;
    this->day = 0;
    this->hour = 0;
    this->minute = 0;

    this->setDateAsString();

    this->days = new int[1];
    this->days[0] = 0;

    DateTime::objectsCounter++;
}

DateTime::DateTime(const DateTime &other) {
    std::cout << "Вызван конструктор копирования для объекта в " << this << std::endl;

    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    this->hour = other.hour;
    this->minute = other.minute;

    this->setDateAsString();

    int daysSize = this->daysInMonth(other.month, other.year);
    this->days = new int[daysSize];
    for (int i = 0; i < daysSize; i++) {
        this->days[i] = other.days[i];
    }

    DateTime::objectsCounter++;
}

DateTime::~DateTime() {
    std::cout << "Вызван деструктор для объекта в " << this << std::endl;

    delete[] this->days;
    DateTime::objectsCounter--;
}

void DateTime::plusYear() {
    this->setYear(this->year + 1);
    this->setDateAsString();
}

void DateTime::minusYear() {
    this->setYear(this->year - 1);
    this->setDateAsString();
}

void DateTime::plusMonth() {
    this->setMonth(this->month + 1);
    this->setDateAsString();
}

void DateTime::minusMonth() {
    this->setMonth(this->month - 1);
    this->setDateAsString();
}

void DateTime::plusDay() {
    this->setDay(this->day + 1);
    this->setDateAsString();
}

void DateTime::minusDay() {
    this->setDay(this->day - 1);
    this->setDateAsString();
}

void DateTime::plusHour() {
    this->setHour(this->hour + 1);
    this->setDateAsString();
}

void DateTime::minusHour() {
    this->setHour(this->hour - 1);
    this->setDateAsString();
}

void DateTime::plusMinute() {
    this->setMinute(this->minute + 1);
    this->setDateAsString();
}

void DateTime::minusMinute() {
    this->setMinute(this->minute - 1);
    this->setDateAsString();
}

void DateTime::printDateTime() {
    std::cout << this->dateAsString << std::endl;
}

int DateTime::getObjectsCounter() {
    return DateTime::objectsCounter;
}
