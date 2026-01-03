#ifndef MODELING_KR_SHOP_H
#define MODELING_KR_SHOP_H

#include "Client.h"
#include "Clerk.h"
#include "List.h"

class Shop {
    static const int accumulation = 1;
    
    ListNode<Client>* queue;
    Clerk** workers;
    int q_length;
    int to_arrival;

public:
    explicit Shop(Clerk** w);
    ~Shop();
    
    void Arrival();
    void run();
    int Choice();
};

#endif //MODELING_KR_SHOP_H
