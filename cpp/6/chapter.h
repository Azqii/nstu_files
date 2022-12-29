#pragma once

#include <iostream>
#include <string>

// Класс главы
class Chapter
{
private:
    std::string chapter_name; // Название главы

    int pages_amount; // Количество страниц

public:
    Chapter(std::string chapter_name,
            int pages_amount);

    Chapter();

    std::string get_name();
    void set_name(std::string name);

    int get_pages();
    void set_pages(int amount);
};