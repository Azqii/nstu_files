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

    void changeYear(int value); // Смена данных в поле года

    void changeMonth(int value); // Смена данных в поле месяца

    void changeDay(int value); // Смена данных поля дней

    void changeHour(int value); // Смена данных поля часов

    void changeMinute(int value); // Смена данных поля минут

public:
    DateTime(int year, int month, int day, int hour, int minute); // Конструктор с параметрами.

    DateTime(); // Конструктор без параметров

    void change(int year, int month, int day, int hour, int minute); // Метод для смены даты

    int getYear() const; // Геттер поля года

    int getMonth() const; // Геттер поля месяца

    DateTime operator-(const DateTime &other) const; // Перегрузка оператора вычитания

    DateTime &operator=(const DateTime &other); // Перегрузка оператора присваивания

    bool operator>(const DateTime &other) const; // Перегруженный оператор сравнения

    bool operator<(const DateTime &other) const; // Перегруженный оператор сравнения

    friend std::ostream &operator<<(std::ostream &os, const DateTime &dateTime); // Перегрузка оператора потока вывода

    friend std::istream &operator>>(std::istream &is, DateTime &dateTime); // Перегрузка оператора потока ввода

    friend std::fstream &operator<<(std::fstream &os, const DateTime &dateTime); // Перегрузка потока вывода в файл

    friend class Rental; // Дружественный класс
};


#endif //CRS_DATETIME_H
