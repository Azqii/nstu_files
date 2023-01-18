//
// Created by dima on 04.01.23.
//

#ifndef OOP6_DATETIME_H
#define OOP6_DATETIME_H

#include <iostream>
#include <string>
#include <fstream>


class DateTime {
protected:
    int
        year, // Год.
        month, // Месяц.
        day, // День.
        hour, // Час.
        minute; // Минута.

    // Поле с динамическим выделением памяти для хранения чисел месяца.
    // При использовании конструктора без параметров хранит в себе число 0.
    // Сделано исключительно в учебных целях, поле с практической пользой для данного класса я придумать не смог.
    int *days;

    std::string dateAsString; // Строковое представление даты.

    static int objectsCounter; // Статический счетчик существующих объектов.

protected:
    void setDateAsString(); // Сеттер для поля строкового представления даты.

    void setDays(); // Сеттер для поля с динамическим выделением памяти

    void setYear(int value); // Сеттер для поля года.

    void setMonth(int value); // Сеттер для поля месяца.

    void setDay(int value); // Сеттер для поля дня.

    void setHour(int value); // Сеттер для поля часа.

    void setMinute(int value); // Сеттер для поля минуты.

    static int daysInMonth(int monthNumber, int yearNumber); // Метод для определения количества дней в месяце.

public:
    DateTime(int year, int month, int day, int hour, int minute); // Конструктор с параметрами.

    DateTime(); // Конструктор по умолчанию (без параметров).

    DateTime(const DateTime &other); // Конструктор копирования.

    ~DateTime(); // Деструктор.

    void plusYear(); // Прибавляет 1 год.

    void minusYear(); // Отнимает 1 год.

    void plusMonth(); // Прибавляет 1 месяц.

    void minusMonth(); // Отнимает 1 месяц.

    void plusDay(); // Прибавляет 1 день.

    void minusDay(); // Отнимает 1 день.

    virtual void plusHour(); // Прибавляет 1 час.

    virtual void minusHour(); // Отнимает 1 час.

    virtual void plusMinute(); // Прибавляет 1 минуту.

    virtual void minusMinute(); // Отнимает 1 минуту.

    void printDateTime(); // Распечатывает время и дату.

    static int getObjectsCounter(); // Геттер счетчика объектов.

    DateTime &operator=(const DateTime &other); // Перегрузка оператора присваивания

    DateTime operator+(const DateTime &other) const; // Перегрузка оператора сложения

    DateTime operator-(const DateTime &other) const; // Перегрузка оператора вычитания

    virtual operator char *(); // Преобразование к типу char*

    void binWrite(std::fstream &file); // Метод для записи в бинарный файл

    void binRead(std::fstream &file); // Метод для чтения из бинарного файла

    friend std::ostream &operator<<(std::ostream &os, const DateTime &dateTime); // Перегрузка оператора потока вывода

    friend std::istream &operator>>(std::istream &is, DateTime &dateTime); // Перегрузка оператора потока ввода

    friend std::fstream &operator<<(std::fstream &os, const DateTime &dateTime); // Перегрузка потока вывода в файл
};


#endif //OOP6_DATETIME_H
