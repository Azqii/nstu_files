//
// Created by dima on 28.12.22.
//

#include "DateTime.h"


int DateTime::objectsCounter = 0; // Присваивание значения статическому полю.

DateTime::DateTime(int year, int month, int day, int hour, int minute) {
    if (month > 12 || month <= 0 || day > DateTime::daysInMonth(month, year) || day <= 0 ||
        hour > 23 || hour < 0 || minute < 0 || minute > 59)
        throw std::invalid_argument("Такой даты не существует");

    std::cout << "Вызван конструктор с параметрами для объекта в " << this << std::endl;

    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;

    this->setDateAsString();
    this->setDays();

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
    this->setDays();

    DateTime::objectsCounter++;
}

DateTime::~DateTime() {
    std::cout << "Вызван деструктор для объекта в " << this << std::endl;
    delete[] this->days;
    DateTime::objectsCounter--;
}

void DateTime::setYear(int value) {
    this->year = value;

    this->setDateAsString();
}

void DateTime::setMonth(int value) {
    if (value > 12) {
        int addYears = (value - 1) / 12;
        this->setYear(this->year + addYears);
        value = (value - 1) % 12 + 1;
    } else if (value <= 0) {
        value--;
        int minusYears = value / 12 - 1;
        this->setYear(this->year + minusYears);
        value = 12 + (value + 1) % 12;
    }

    this->month = value;

    this->setDateAsString();

    delete[] this->days;
    this->setDays();
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
        throw std::invalid_argument("Сначала измените значение месяца");

    int currentMonthDays = DateTime::daysInMonth(this->month, this->year);
    // Рассчитано только на прибавление/убавление одного месяца из-за разного кол-ва дней в месяцах.
    if (value > currentMonthDays) {
        this->setMonth(this->month + 1);
        value = value - currentMonthDays;
    } else if (value <= 0) {
        this->setMonth(this->month - 1);
        value = DateTime::daysInMonth(this->month, this->year) + value;
    }

    this->day = value;

    this->setDateAsString();
}

void DateTime::setHour(int value) {
    if (value > 23) {
        int addDays = value / 24;
        this->setDay(this->day + addDays);
        value = value % 24;
    } else if (value < 0) {
        int minusDays = value / 24 - 1;
        this->setDay(this->day + minusDays);
        value = 24 + value % 24;
    }

    this->hour = value;

    this->setDateAsString();
}

void DateTime::setMinute(int value) {
    if (value > 59) {
        int addHours = value / 60;
        this->setHour(this->hour + addHours);
        value = value % 60;
    } else if (value < 0) {
        int minusHours = value / 60 - 1;
        this->setHour(this->hour + minusHours);
        value = 60 + value % 60;
    }

    this->minute = value;

    this->setDateAsString();
}

void DateTime::setDateAsString() {
    this->dateAsString =
            std::to_string(this->day) + "." + std::to_string(this->month) + "." + std::to_string(this->year) + " " +
            std::to_string(this->hour) + ":" + std::to_string(this->minute);
}

void DateTime::setDays() {
    int daysSize = DateTime::daysInMonth(this->month, this->year);
    this->days = new int[daysSize];
    for (int i = 0; i < daysSize; i++) {
        this->days[i] = i + 1;
    }
}

void DateTime::plusYear() {
    this->setYear(this->year + 1);
}

void DateTime::minusYear() {
    this->setYear(this->year - 1);
}

void DateTime::plusMonth() {
    this->setMonth(this->month + 1);
}

void DateTime::minusMonth() {
    this->setMonth(this->month - 1);
}

void DateTime::plusDay() {
    this->setDay(this->day + 1);
}

void DateTime::minusDay() {
    this->setDay(this->day - 1);
}

void DateTime::plusHour() {
    this->setHour(this->hour + 1);
}

void DateTime::minusHour() {
    this->setHour(this->hour - 1);
}

void DateTime::plusMinute() {
    this->setMinute(this->minute + 1);
}

void DateTime::minusMinute() {
    this->setMinute(this->minute - 1);
}

void DateTime::printDateTime() {
    std::cout << this->dateAsString << std::endl;
}

int DateTime::getObjectsCounter() {
    return DateTime::objectsCounter;
}
