#include "Clerk.h"
#include "globals.h"
#include "random.h"
#include "normal.h"

Clerk::Clerk(int i) {
    id = i;
    queue = new Client*[MAX_CLIENT];
    for (int j = 0; j < MAX_CLIENT; j++)
        queue[j] = nullptr;
    serving = nullptr;
    units = -1;
    to_dpath = -1;
    to_bpath = -1;
    to_calculate = -1;
    to_search = -1;
    from_order = -1;
}

Clerk::~Clerk() {
    for (int i = 0; i < QLength(); i++)
        delete queue[i];
    delete[] queue;
    if (serving)
        delete serving;
}

int Clerk::QLength() {
    for (int k = 0; k < MAX_CLIENT; k++)
        if (queue[k] == nullptr)
            return k;
    return MAX_CLIENT;
}

int Clerk::GetState() {
    if (units == -1) return 0;
    if (to_dpath > 0) return 1;
    if (to_search > 0) return 2;
    if (to_bpath > 0) return 3;
    if (to_calculate > 0) return 4;
    return 0;
}

ListNode<Client>* Clerk::TakeOrder(ListNode<Client>* q, int acc) {
    ListNode<Client>* ptr = q;
    for (int i = 0; i < acc; i++) {
        queue[i] = ptr->Data();
        ptr = ptr->Next();
    }
    units = acc;
    from_order = 0;
    to_dpath = get_uniform(path_ave, path_offset);
    total_ordered++;
    orders_ave = orders_ave * (1 - 1.0f / total_ordered) + ((float)units) / total_ordered;
    fprintf(order, "%d\n", acc);
    return ptr;
}

void Clerk::Arrival() {
    to_dpath = -1;
    to_search = (int)(get_normal(3.0f * units, 0.6f * units, 0.01f) * 60);
    if (to_search <= 0)
        to_search = 1;
}

void Clerk::TakeAll() {
    to_search = -1;
    to_bpath = get_uniform(path_ave, path_offset);
}

void Clerk::ComeBack() {
    to_bpath = -1;
    serving = queue[0];
    for (int i = 0; i < (MAX_CLIENT - 1); i++)
        queue[i] = queue[i + 1];
    queue[MAX_CLIENT - 1] = nullptr;
    to_calculate = get_uniform(money_ave, money_offset);
}

void Clerk::Completed() {
    to_calculate = -1;
    completed++;
    soj_ave = soj_ave * (1 - 1.0f / completed) + (float)(serving->time) / completed;
    fprintf(sojourn, "%.3f\n", (float)(serving->time) / 60);
    delete serving;
    serving = nullptr;
    
    if (QLength() == 0) {
        units = -1;
        serve_ave = serve_ave * (1 - 1.0f / total_ordered) + ((float)from_order) / total_ordered;
        from_order = -1;
        return;
    }
    
    serving = queue[0];
    for (int i = 0; i < (MAX_CLIENT - 1); i++)
        queue[i] = queue[i + 1];
    queue[MAX_CLIENT - 1] = nullptr;
    to_calculate = get_uniform(money_ave, money_offset);
}

void Clerk::run() {
    if (to_dpath > 0) to_dpath--;
    if (to_dpath == 0) Arrival();
    if (to_bpath > 0) to_bpath--;
    if (to_bpath == 0) ComeBack();
    if (to_calculate > 0) to_calculate--;
    if (to_calculate == 0) Completed();
    if (to_search > 0) to_search--;
    if (to_search == 0) TakeAll();
    if (units != -1) {
        from_order++;
        ro[id - 1]++;
    }
}
