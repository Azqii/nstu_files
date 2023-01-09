//
// Created by dima on 07.01.23.
//

#ifndef CRS_RENTAL_H
#define CRS_RENTAL_H

#include "DateTime.h"


class Rental {
private:
    char
            *objectName,
            *customerName;

    int
            pricePerDay;

    DateTime
            receiveTime,
            returnTime;

private:
    void setObjectName(const char *value);

    void setCustomerName(const char *value);

public:

    Rental(const char *objectName, const char *customerName, int pricePerDay, DateTime receiveTime);

    Rental();

    ~Rental();

    void setReturnTime(DateTime returnTime);

    int calculateOverallPrice();

    DateTime getReceiveTime() const;

    bool operator>(const Rental &other) const;

    bool operator<(const Rental &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Rental &rental);
};


#endif //CRS_RENTAL_H
