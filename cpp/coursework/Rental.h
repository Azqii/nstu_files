//
// Created by dima on 07.01.23.
//

#ifndef CRS_RENTAL_H
#define CRS_RENTAL_H

#include "DateTime.h"


class Rental {
private:
    char
            *objectName, // Название арендуемого объекта
            *customerName; // Имя арендатора

    int
            pricePerDay; // Цена в день

    DateTime
            receiveTime, // Время получения
            returnTime; // Время возврата

public:
    // Конструктор с параметрами
    Rental(const char *objectName, const char *customerName, int pricePerDay, DateTime receiveTime);

    Rental(); // Конструктор по умолчанию

    ~Rental(); // Деструктор

    void setReturnTime(DateTime returnTime); // Сеттер для времени возврата

    int calculateOverallPrice(); // Метод вычисления стоимости за всё время

    DateTime getReceiveTime() const; // Гетер даты получения

    bool operator>(const Rental &other) const; // Перегруженный оператор сравнения

    bool operator<(const Rental &other) const; // Перегруженный оператор сравнения

    void binWrite(std::fstream &file); // Запись в бинарный файл

    void binRead(std::fstream &file); // Чтение из бинарного файла

    friend std::ostream &operator<<(std::ostream &os, const Rental &rental); // Перегрузка потока вывода
};


#endif //CRS_RENTAL_H
