//
// Created by Dima on 02.12.2025.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>  // comment on Linux
#include "Hashtable.h"

#pragma execution_character_set("utf-8")

using std::string, std::to_string, std::cout, std::endl;


string genkey() {
    static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int length = 5 + rand() % 11; // от 5 до 15 символов

    string key;
    key.reserve(length);

    for (int i = 0; i < length; ++i)
        key.push_back(alphabet[rand() % alphabet.size()]);

    return key;
}


string BigO(double alpha) {
    double estimate = 1.0 + alpha / 2.0;

    return "Теоретическая оценка трудоемкости операций: " + to_string(estimate);
}


void test(int n, double alpha) {
    Hashtable<int> table(n);

    // k — количество ключей для вставки
    int k = table.getCapacity() * alpha;

    // массив для ключей, которые присутствуют
    string *m = new string[k];

    // заполнение таблицы и массива элементами со случайными ключами
    for (int i = 0; i < k; i++) {
        m[i] = genkey();
        table.insert(m[i], 1);
    }

    // вывод размера таблицы и альфы до теста
    cout << "До тестов" << endl;
    cout << "Размер таблицы: " << table.getSize() << endl;
    cout << "Альфа: " << (double) table.getSize() / table.getCapacity() << endl;

    // обнуление счётчиков трудоёмкости операций
    double I = 0, D = 0, S = 0;

    // цикл операций, 10% — промахи
    for (int i = 0; i < k / 2; i++) {
        if (i % 10 == 0) { // 10% промахов
            table.remove(genkey());
            D += table.getLastProbeCount();

            table.insert(m[rand() % k], 1);
            I += table.getLastProbeCount();

            table.find(genkey());
            S += table.getLastProbeCount();
        } else { // 90% успешных операций
            int ind = rand() % k;

            table.remove(m[ind]);
            D += table.getLastProbeCount();

            string key = genkey();
            table.insert(key, 1);
            I += table.getLastProbeCount();

            m[ind] = key;

            table.find(m[rand() % k]);
            S += table.getLastProbeCount();
        }
    }

    // вывод размера и альфы после теста
    cout << endl << "После тестов:" << endl;
    cout << "Размер таблицы: " << table.getSize() << endl;
    cout << "Альфа: " << (double) table.getSize() / table.getCapacity() << endl;

    // вывод теоретических оценок
    cout << endl << BigO(alpha) << endl;

    // вывод экспериментальных результатов
    cout << "Вставка: " << I / (k / 2.0) << endl;
    cout << "Поиск: " << S / (k / 2.0) << endl;
    cout << "Удаление: " << D / (k / 2.0) << endl;

    delete[] m;
}

int main() {
    SetConsoleOutputCP(65001);  // Comment on linux
    SetConsoleCP(65001);  // Comment on linux

    srand(time(nullptr));

    int n = 1000;       // максимальное число ключей
    double alpha = 10; // коэффициент заполнения
    test(n, alpha);

    return 0;
}
