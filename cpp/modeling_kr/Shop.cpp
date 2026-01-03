#include "Shop.h"
#include "globals.h"
#include "random.h"
#include <cstdlib>

Shop::Shop(Clerk** w) {
    workers = w;
    queue = nullptr;
    q_length = 0;
    to_arrival = (int)(get_exp(0.5f) * 60);
}

Shop::~Shop() {
    while (queue)
        queue = ListDelete<Client>(queue, queue);
}

int Shop::Choice() {
    int k = 0;
    int mas[3];
    
    for (int i = 0; i < 3; i++) {
        if (workers[i]->GetState() == 0) {
            mas[k] = i;
            k++;
        }
    }
    
    if (k == 0) return -1;
    if (k == 1) return mas[0];
    return mas[rand() % k];
}

void Shop::Arrival() {
    to_arrival = (int)(get_exp(0.5f) * 60);
    if (to_arrival == 0)
        to_arrival = 1;
    
    entered++;
    Client* p = new Client(entered);
    ListNode<Client>* ptr = new ListNode<Client>(p, nullptr);
    
    if (q_length == 0) {
        queue = ptr;
        q_length = 1;
        return;
    }
    
    ListAdd<Client>(queue, ptr);
    q_length++;
}

void Shop::run() {
    if (to_arrival > 0) to_arrival--;
    if (to_arrival == 0) Arrival();
    
    int p = (q_length < MAX_CLIENT) ? q_length : MAX_CLIENT;
    
    if (p >= accumulation) {
        int k = Choice();
        if (k != -1) {
            queue = workers[k]->TakeOrder(queue, p);
            q_length -= p;
        }
    }
    
    if (queue) {
        ListNode<Client>* ptr = queue;
        while (ptr) {
            (ptr->Data()->time)++;
            ptr = ptr->Next();
        }
    }
    
    for (int i = 0; i < M; i++) {
        if (workers[i]->serving != nullptr)
            (workers[i]->serving->time)++;
        for (int j = 0; j < MAX_CLIENT; j++) {
            if (workers[i]->queue[j] != nullptr)
                (workers[i]->queue[j]->time)++;
        }
    }
    
    p = q_length;
    for (int k = 0; k < M; k++) {
        p += workers[k]->QLength();
        if (workers[k]->GetState() == 4)
            p++;
    }
    
    if ((total + 1) % 60 == 0) {
        int t = (total + 1) / 60;
        fprintf(num, "%d\n", p);
        num_ave = num_ave * (1 - 1.0f / t) + ((float)p) / t;
        que1_ave = que1_ave * (1 - 1.0f / t) + ((float)q_length) / t;
        
        int busy_count = 0;
        for (int c = 0; c < M; c++) {
            if (workers[c]->GetState() != 0)
                busy_count++;
        }
        busy_ave = busy_ave * (1 - 1.0f / t) + ((float)busy_count) / t;
    }
}
