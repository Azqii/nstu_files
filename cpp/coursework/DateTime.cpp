//
// Created by dima on 06.01.23.
//

#include "DateTime.h"


int DateTime::daysInMonth(int monthNumber, int yearNumber) {
    switch (monthNumber) {
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

DateTime::DateTime(int year, int month, int day, int hour, int minute) {
    if (month > 12 || month <= 0 || day > DateTime::daysInMonth(month, year) || day <= 0 ||
        hour > 23 || hour < 0 || minute < 0 || minute > 59)
        throw std::invalid_argument("Такой даты не существует");

    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
}

DateTime::DateTime() {
    this->year = 0;
    this->month = 0;
    this->day = 0;
    this->hour = 0;
    this->minute = 0;
}

void DateTime::changeYear(int value) {
    this->year = value;
}

void DateTime::changeMonth(int value) {
    if (value > 12) {
        int addYears = (value - 1) / 12;
        this->changeYear(this->year + addYears);
        value = (value - 1) % 12 + 1;
    } else if (value <= 0) {
        value--;
        int minusYears = value / 12 - 1;
        this->changeYear(this->year + minusYears);
        value = 12 + (value + 1) % 12;
    }

    this->month = value;
}

void DateTime::changeDay(int value) {
    if (this->month == 0)
        throw std::invalid_argument("Сначала измените значение месяца");

    int currentMonthDays = DateTime::daysInMonth(this->month, this->year);
    // Рассчитано только на прибавление/убавление одного месяца из-за разного кол-ва дней в месяцах.
    if (value > currentMonthDays) {
        this->changeMonth(this->month + 1);
        value = value - currentMonthDays;
    } else if (value <= 0) {
        this->changeMonth(this->month - 1);
        value = DateTime::daysInMonth(this->month, this->year) + value;
    }

    this->day = value;
}

void DateTime::changeHour(int value) {
    if (value > 23) {
        int addDays = value / 24;
        this->changeDay(this->day + addDays);
        value = value % 24;
    } else if (value < 0) {
        int minusDays = value / 24 - 1;
        this->changeDay(this->day + minusDays);
        value = 24 + value % 24;
    }

    this->hour = value;
}

void DateTime::changeMinute(int value) {
    if (value > 59) {
        int addHours = value / 60;
        this->changeHour(this->hour + addHours);
        value = value % 60;
    } else if (value < 0) {
        int minusHours = value / 60 - 1;
        this->changeHour(this->hour + minusHours);
        value = 60 + value % 60;
    }

    this->minute = value;
}

void DateTime::change(int year, int month, int day, int hour, int minute) {
    this->changeYear(year);
    this->changeMonth(month);
    this->changeDay(day);
    this->changeHour(hour);
    this->changeMinute(minute);
}

int DateTime::getYear() const {
    return year;
}

int DateTime::getMonth() const {
    return month;
}

DateTime &DateTime::operator=(const DateTime &other) {
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    this->hour = other.hour;
    this->minute = other.minute;

    return *this;
}

DateTime DateTime::operator-(const DateTime &other) const {
    DateTime tmp;
    tmp.changeYear(this->year - other.year);
    tmp.changeMonth(this->month - other.month);
    tmp.changeDay(this->day - other.day);
    tmp.changeHour(this->hour - other.hour);
    tmp.changeMinute(this->minute - other.minute);

    return tmp;
}

bool DateTime::operator>(const DateTime &other) const {
    if (this->year != other.year)
        return this->year > other.year;
    else if (this->month != other.month)
        return this->month > other.month;
    else if (this->day != other.day)
        return this->day > other.day;
    else if (this->hour != other.hour)
        return this->hour > other.hour;
    else
        return this->minute > other.minute;

}

bool DateTime::operator<(const DateTime &other) const {
    return other > *this;
}

std::ostream &operator<<(std::ostream &os, const DateTime &dateTime) {
    os << dateTime.day << "." << dateTime.month << "." << dateTime.year << " " << dateTime.hour << ":"
       << dateTime.minute;
    return os;
}

std::istream &operator>>(std::istream &is, DateTime &dateTime) {
    int year, month, day, hour, minute;
    is >> year >> month >> day >> hour >> minute;
    dateTime = DateTime(year, month, day, hour, minute);
    return is;
}
