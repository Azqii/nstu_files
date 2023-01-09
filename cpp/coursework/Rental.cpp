//
// Created by dima on 07.01.23.
//

#include <cstring>
#include "Rental.h"

Rental::Rental(const char *objectName, const char *customerName, int pricePerDay, DateTime receiveTime) {
    this->setObjectName(objectName);
    this->setCustomerName(customerName);
    this->pricePerDay = pricePerDay;
    this->receiveTime = receiveTime;
}



Rental::Rental() {
    this->objectName = "";
    this->customerName = "";
    this->pricePerDay = 0;
    this->receiveTime = DateTime();
}

Rental::~Rental() {
    delete[] this->objectName;
    delete[] this->customerName;
}

void Rental::setObjectName(const char *value) {
    this->objectName = new char[strlen(value) + 1];
    std::strcpy(this->objectName, value);
}

void Rental::setCustomerName(const char *value) {
    this->customerName = new char[strlen(value) + 1];
    std::strcpy(this->customerName, value);
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

std::ostream &operator<<(std::ostream &os, const Rental &rental) {
    os << "Предмет: " << rental.objectName << " | Имя: " << rental.customerName << " | Цена: " << rental.pricePerDay
       << " | Время выдачи: " << rental.receiveTime << " | Время возврата: " << rental.returnTime;

    return os;
}
