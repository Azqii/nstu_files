#pragma once

#include <vector>
#include "chapter.h"

// Класс книги
class Book
{
private:
    std::string
            author_name,      // Имя автора
    book_name,        // Название книги
    publishing_house; // Издательство

    int year; // Год выпуска

    std::string
            type; // Тип

    long long int ISBN; // ISBN

    bool got_published; // Состояние публикации

    std::vector<Chapter> chapters; // Контейнер с главами

public:
    Book(std::string author_name,
         std::string book_name,
         std::string type);

    Book();

    std::string get_author();

    void set_author(std::string author_name);

    std::string get_name();

    void set_name(std::string book_name);

    std::string get_type();

    void set_type(std::string type);

    void publish(std::string publishing_house, int year, long long int ISBN);

    void add_chapter(Chapter chapter);

    void del_chapter(int number);

    void change_chapter(int number, std::string new_name, int new_pages);

    void print_chapters();
};