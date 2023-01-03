//
// Created by dima on 03.01.23.
//

#include "Time.h"


Time::Time(int year, int month, int day, int hour, int minute) : DateTime(year, month, day, hour, minute) {
    this->setTimeAsString();
}

Time::Time() {
    this->setTimeAsString();
}

Time::Time(const Time &other) : DateTime(other) {
    this->setTimeAsString();
}

void Time::setTimeAsString() {
    this->timeAsString = std::to_string(this->hour) + ":" + std::to_string(this->minute);
}

void Time::changeTime(int hour, int minute) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
        throw std::invalid_argument("Такого времени не существует");
    else if (abs(this->hour - hour) > 12 || (this->hour - hour == -12 && this->minute < minute) ||
             (this->hour - hour == 12 && this->minute > minute))
        throw std::invalid_argument("Время можно изменять только в диапазоне 0 - 12 часов.");

    this->setHour(hour);
    this->setMinute(minute);

    this->setDateAsString();
    this->setTimeAsString();
}

void Time::printTime() {
    std::cout << this->timeAsString << std::endl;
}

void Time::plusHour() {
    DateTime::plusHour();
    this->setTimeAsString();
}

void Time::minusHour() {
    DateTime::minusHour();
    this->setTimeAsString();
}

void Time::plusMinute() {
    DateTime::plusMinute();
    this->setTimeAsString();
}

void Time::minusMinute() {
    DateTime::minusMinute();
    this->setTimeAsString();
}
