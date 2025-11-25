#include <iostream>
#include <string>
#include <windows.h>  // comment on Linux
#include "Hashtable.h"

#pragma execution_character_set("utf-8")

using std::cout, std::cin, std::endl, std::string;

int main() {
    SetConsoleOutputCP(65001);  // Comment on linux
    SetConsoleCP(65001);  // Comment on linux

    Hashtable<int> table(10);
    Hashtable<int>::Iterator it = table.begin();

    int x;
    while (true) {
        cout << endl << "Выбор действия:" << endl << endl;
        cout << "1. Создать хеш-таблицу с заданной ёмкостью" << endl;
        cout << "2. Вставить элемент (key, value)" << endl;
        cout << "3. Удалить элемент по ключу" << endl;
        cout << "4. Найти элемент по ключу" << endl;
        cout << "5. Показать таблицу" << endl;
        cout << "6. Показать size и capacity" << endl;
        cout << "7. Показать h(k) и кол-во проб последней операции" << endl;
        cout << "8. Проверка на пустоту" << endl;
        cout << "9. Очистка" << endl;
        cout << "10. Обнулить итератор" << endl;
        cout << "11. Показать содержимое итератора" << endl;
        cout << "12. Перевести итератор на следующий элемент" << endl;
        cout << "13. Присвоить итератору новое значение (cin >> *it)" << endl;

        cout << endl;
        cin >> x;
        cout << endl;

        try {
            switch (x) {
                case 1: {
                    size_t cap;
                    cin >> cap;

                    table.~Hashtable();
                    new (&table) Hashtable<int>(cap);
                    break;
                }
                case 2: {
                    string key;
                    int value;
                    cin >> key >> value;

                    cout << table.insert(key, value) << endl;
                    break;
                }
                case 3: {
                    string key;
                    cin >> key;

                    cout << table.remove(key) << endl;
                    break;
                }
                case 4: {
                    string key;
                    cin >> key;

                    cout << *table.find(key) << endl;
                    break;
                }
                case 5: {
                    table.show();
                    break;
                }
                case 6: {
                    cout << "size = " << table.getSize() << endl;
                    cout << "capacity = " << table.getCapacity() << endl;
                    break;
                }
                case 7: {
                    cout << "h(k) = " << table.getLastHash() << endl;
                    cout << "Кол-во проб = " << table.getLastProbeCount() << endl;
                    break;
                }
                case 8: {
                    cout << table.isEmpty() << endl;
                    break;
                }
                case 9: {
                    table.clear();
                    break;
                }
                case 10: {
                    it = table.begin();
                    break;
                }
                case 11: {
                    cout << *it << endl;
                    break;
                }
                case 12: {
                    ++it;
                    break;
                }
                case 13: {
                    cin >> *it;
                    break;
                }
                default: {
                    cout << "Такой команды не существует" << endl;
                    break;
                }
            }
        }
        catch (...) {
            cout << "Исключение" << endl;
        }
    }
    return 0;
}
