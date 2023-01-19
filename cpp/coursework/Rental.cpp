//
// Created by dima on 07.01.23.
//

#include <cstring>
#include "Rental.h"

Rental::Rental(const char *objectName, const char *customerName, int pricePerDay, DateTime receiveTime) {
    this->objectName = new char[strlen(objectName) + 1];
    std::strcpy(this->objectName, objectName);

    this->customerName = new char[strlen(customerName) + 1];
    std::strcpy(this->customerName, customerName);

    this->pricePerDay = pricePerDay;
    this->receiveTime = receiveTime;
}

Rental::Rental() {
    this->objectName = nullptr;
    this->customerName = nullptr;
    this->pricePerDay = int();
    this->receiveTime = DateTime();
}

Rental::~Rental() {
    delete[] this->objectName;
    delete[] this->customerName;
}

void Rental::setReturnTime(DateTime value) {
    if (value < this->receiveTime)
        throw std::invalid_argument("Дата возврата не может быть меньше даты приема");
    else if (this->returnTime.year != 0 && this->returnTime.month != 0 && this->returnTime.day != 0)
        throw std::invalid_argument("Дата возврата уже назначена");

    this->returnTime = value;
}

int Rental::calculateOverallPrice() {
    if (this->returnTime.year == 0 && this->returnTime.month == 0 && this->returnTime.day == 0)
        throw std::logic_error("Стоимость нельзя посчитать, пока арендуемый предмет не вернули");

    DateTime duration = this->returnTime - this->receiveTime;
    int days = duration.year * 12 * 30 + duration.month * 30 + duration.day + 1;

    return this->pricePerDay * days;
}

DateTime Rental::getReceiveTime() const {
    return this->receiveTime;
}

bool Rental::operator>(const Rental &other) const {
    return this->receiveTime > other.receiveTime;
}

bool Rental::operator<(const Rental &other) const {
    return this->receiveTime < other.receiveTime;
}

void Rental::binWrite(std::fstream &file) {
    if (!file.is_open())
        throw std::invalid_argument("Файл не открыт");

    // Запись поля названия объекта
    unsigned int len = strlen(this->objectName);
    file.write((char *) &len, sizeof(len));
    file.write(this->objectName, len);

    // Запись поля имени арендатора
    len = strlen(this->customerName);
    file.write((char *) &len, sizeof(len));
    file.write(this->customerName, len);

    // Запись остальных полей
    file.write((char *) &this->pricePerDay, sizeof(this->pricePerDay));
    file.write((char *) &this->receiveTime, sizeof(this->receiveTime));
    file.write((char *) &this->returnTime, sizeof(this->returnTime));
}

void Rental::binRead(std::fstream &file) {
    if (!file.is_open())
        throw std::invalid_argument("Файл не открыт");

    unsigned int len;

    // Считывание поля названия объекта
    delete[] this->objectName;
    file.read((char *) &len, sizeof(len));
    this->objectName = new char[len + 1];
    file.read(this->objectName, len);
    this->objectName[len] = '\0';

    // Считывание поля имени арендатора
    delete[] this->customerName;
    file.read((char *) &len, sizeof(len));
    this->customerName = new char[len + 1];
    file.read(this->customerName, len);
    this->objectName[len] = '\0';

    // Считывание остальных полей
    file.read((char *) &this->pricePerDay, sizeof(this->pricePerDay));
    file.read((char *) &this->receiveTime, sizeof(this->receiveTime));
    file.read((char *) &this->returnTime, sizeof(this->returnTime));
}

std::ostream &operator<<(std::ostream &os, const Rental &rental) {
    os << "Предмет: " << rental.objectName << " | Имя: " << rental.customerName << " | Цена: " << rental.pricePerDay
       << " | Время выдачи: " << rental.receiveTime << " | Время возврата: " << rental.returnTime;

    return os;
}
