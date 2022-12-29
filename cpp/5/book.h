#pragma once

#include <iostream>
#include <string>

// Класс книги
class Book
{
private:
    std::string
            author_name,      // Имя автора
    book_name,        // Название книги
    publishing_house; // Издатель

    int year,            // Год выпуска
    pages_amount,    // Кол-во страниц
    chapters_amount; // Кол-во глав

    std::string
            type; // Тип

    long long int ISBN; // ISBN

    bool got_published; // Состояние публиакции

public:
    Book(std::string author_name,
         std::string book_name,
         std::string publishing_house,
         int year,
         int pages_amount,
         int chapters_amount,
         std::string type,
         long long int ISBN);

    Book();

    std::string get_author();
    void set_author(std::string author_name);

    std::string get_name();
    void set_name(std::string book_name);

    std::string get_type();
    void set_type(std::string type);

    void set_size(int chapters, int pages);

    double pages_per_chapter();

    void publish(std::string publishing_house, int year, long long int ISBN);
};