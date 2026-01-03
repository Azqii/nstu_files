#ifndef MODELING_KR_CLERK_H
#define MODELING_KR_CLERK_H

#include "Client.h"
#include "List.h"

class Clerk {
    static const int path_ave = 60;
    static const int path_offset = 30;
    static const int money_ave = 120;
    static const int money_offset = 60;
    
    int id;
    Client** queue;
    Client* serving;
    int units;
    int to_dpath;
    int to_bpath;
    int to_calculate;
    int to_search;
    int from_order;

public:
    friend class Shop;
    
    explicit Clerk(int i);
    ~Clerk();
    
    void Arrival();
    void TakeAll();
    void ComeBack();
    void Completed();
    ListNode<Client>* TakeOrder(ListNode<Client>* q, int acc);
    void run();
    int QLength();
    int GetState();
};

#endif //MODELING_KR_CLERK_H
