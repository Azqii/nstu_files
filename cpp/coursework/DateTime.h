//
// Created by dima on 06.01.23.
//

#ifndef CRS_DATETIME_H
#define CRS_DATETIME_H

#include <iostream>
#include <fstream>


class DateTime {
private:
    int year, // Год.
    month, // Месяц.
    day, // День.
    hour, // Час.
    minute; // Минута.

private:
    static int daysInMonth(int monthNumber, int yearNumber); // Метод для определения количества дней в месяце.

    void changeYear(int value);

    void changeMonth(int value);

    void changeDay(int value);

    void changeHour(int value);

    void changeMinute(int value);

public:
    DateTime(int year, int month, int day, int hour, int minute); // Конструктор с параметрами.

    DateTime(); // Конструктор без параметров

    void change(int year, int month, int day, int hour, int minute);

    int getYear() const;

    int getMonth() const;

    DateTime operator-(const DateTime &other) const; // Перегрузка оператора вычитания

    DateTime &operator=(const DateTime &other); // Перегрузка оператора присваивания

    bool operator>(const DateTime &other) const;

    bool operator<(const DateTime &other) const;

    friend std::ostream &operator<<(std::ostream &os, const DateTime &dateTime); // Перегрузка оператора потока вывода

    friend std::istream &operator>>(std::istream &is, DateTime &dateTime); // Перегрузка оператора потока ввода

    friend std::fstream &operator<<(std::fstream &os, const DateTime &dateTime);

    friend class Rental;
};


#endif //CRS_DATETIME_H
