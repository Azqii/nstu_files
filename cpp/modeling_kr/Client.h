#ifndef MODELING_KR_CLIENT_H
#define MODELING_KR_CLIENT_H

class Client {
    int id;
    int time;
public:
    friend class Clerk;
    friend class Shop;
    explicit Client(int i);
};

#endif //MODELING_KR_CLIENT_H
