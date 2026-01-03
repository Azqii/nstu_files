#include <iostream>
#include <windows.h>  // comment on Linux
#include <ctime>
#include "globals.h"
#include "Shop.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);  // Comment on linux
    SetConsoleCP(65001);  // Comment on linux

    srand(time(nullptr));
    
    int simulation_time = 1000 * 60;
    
    ro = new long int[M];
    for (int i = 0; i < M; i++)
        ro[i] = 0;
    
    sojourn = fopen("sojourn.txt", "w");
    num = fopen("num.txt", "w");
    order = fopen("order.txt", "w");
    
    Clerk** clerks = new Clerk*[M];
    for (int i = 0; i < M; i++)
        clerks[i] = new Clerk(i + 1);
    
    Shop shop(clerks);
    
    for (total = 0; total < simulation_time; total++) {
        shop.run();
        for (int i = 0; i < M; i++)
            clerks[i]->run();
    }
    
    cout << "Всего поступлений " << entered << endl;
    cout << "Обслужено клиентов " << completed << endl;
    cout << "Среднее число занятых клерков " << busy_ave << endl;
    cout << "Среднее время периода занятости клерка " << serve_ave / 60 << endl;
    cout << "Средняя длина первичной очереди " << que1_ave << endl;
    cout << "Среднее число клиентов в магазине " << num_ave << endl;
    cout << "Среднее время пребывания клиента в магазине " << soj_ave / 60 << endl;
    cout << "Средний объем одного заказа " << orders_ave << endl;
    
    fclose(sojourn);
    fclose(num);
    fclose(order);
    
    for (int i = 0; i < M; i++)
        delete clerks[i];
    delete[] clerks;
    delete[] ro;
    
    return 0;
}
