#include "chapter.h"

// Конструктор с параметрами
Chapter::Chapter(std::string chapter_name, int pages_amount)
{
    this->set_name(chapter_name);
    this->set_pages(pages_amount);
}

// Конструктор без параметров
Chapter::Chapter() : Chapter("", 0) {}

// Возвращение названия главы
std::string Chapter::get_name()
{
    return this->chapter_name;
}

// Установка названия главы
void Chapter::set_name(std::string name)
{
    if (name == "")
    {
        this->chapter_name = "Undefined";
        return;
    }
    this->chapter_name = name;
}

// Возвращения кол-ва страниц в главе
int Chapter::get_pages()
{
    return this->pages_amount;
}

// Установка кол-ва страниц в главе
void Chapter::set_pages(int amount)
{
    if (amount < 0)
        throw std::invalid_argument("Кол-во глав не может быть отрицательным");
    this->pages_amount = amount;
}