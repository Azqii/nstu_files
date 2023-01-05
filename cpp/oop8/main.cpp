#include <vector>
#include <map>
#include "DateTime.h"
#include <ctime>
#include <algorithm>


void testSTL() {
    // Создание контейнеров
    std::map<int, DateTime> map;
    std::vector<int> vectorInt;
    std::vector<DateTime> vectorDatetime;

    // Наполнение контейнеров
    unsigned int start_time = clock();
    for (int i = 0; i < 1000; i++)
        map.insert({i, DateTime(2000 + i, i % 12 + 1, i % 28 + 1, i % 24, i % 60)});
    unsigned int stop_time = clock() - start_time;
    std::cout << "Время заполнения словаря с ключом типа int и значением типа пользовательского класса DateTime " <<
              "тысячей элементов = ~" << stop_time << "мс" << std::endl;

    start_time = clock();
    for (int i = 0; i < 1000; i++)
        vectorInt.push_back(i);
    stop_time = clock() - start_time;
    std::cout << "Время заполнения вектора с элементами типа int тысячей элементов = ~" << stop_time << "мс"
              << std::endl;

    start_time = clock();
    for (int i = 0; i < 1000; i++)
        vectorDatetime.emplace_back(2000 + i, i % 12 + 1, i % 28 + 1, i % 24, i % 60);
    stop_time = clock() - start_time;
    std::cout << "Время заполнения вектора с элементами типа пользовательского класса DateTime тысячей элементов = ~"
              << stop_time << "мс" << std::endl;

    std::cout << "\n*******************************************************************************\n" << std::endl;

    // Удаление элементов
    start_time = clock();
    for (auto elem = map.begin(); elem != map.end();) {
        if (elem->first % 2 != 0)
            elem = map.erase(elem);
        else
            elem++;
    }
    stop_time = clock() - start_time;
    std::cout << "Время удаления половины элементов из словаря = ~" << stop_time << "мс" << std::endl;

    start_time = clock();
    for (auto elem = vectorInt.begin(); elem != vectorInt.end();) {
        if (*elem % 2 != 0)
            elem = vectorInt.erase(elem);
        else
            elem++;
    }
    stop_time = clock() - start_time;
    std::cout << "Время удаления половины элементов из вектора с элементами типа int = ~" << stop_time << "мс"
              << std::endl;

    start_time = clock();
    int counter = 0;
    for (auto elem = vectorDatetime.begin(); elem != vectorDatetime.end();) {
        if (counter % 2 != 0)
            elem = vectorDatetime.erase(elem);
        else
            elem++;
    }
    stop_time = clock() - start_time;
    std::cout << "Время удаления половины элементов из вектора с элементами типа DateTime = ~" << stop_time << "мс"
              << std::endl;

    std::cout << "\n*******************************************************************************\n" << std::endl;

    // Поиск
    start_time = clock();
    map.find(500);
    stop_time = clock() - start_time;
    std::cout << "Время поиска элемента в словаре по ключу = ~" << stop_time << "мс" << std::endl;

    std::cout << "\n*******************************************************************************\n" << std::endl;

    // Сортировка
    start_time = clock();
    std::sort(vectorInt.begin(), vectorInt.end(), std::greater<>());
    stop_time = clock() - start_time;
    std::cout << "Время сортировки вектора = ~" << stop_time << "мс" << std::endl;
}

int main() {
    testSTL();
    return 0;
}
