#include "book.h"

// Конструктор с параметрами
Book::Book(std::string author_name,
           std::string book_name,
           std::string publishing_house,
           int year,
           int pages_amount,
           int chapters_amount,
           std::string type,
           long long int ISBN)
{
    this->got_published = false;
    this->set_author(author_name);
    this->set_name(book_name);
    this->set_type(type);
    this->set_size(chapters_amount, pages_amount);
    this->publish(publishing_house, year, ISBN);
}

// Конструктор без параметров
Book::Book() : Book("", "", "", 0, 0, 0, "", 0) {}

// Возвращение имени автора
std::string Book::get_author()
{
    return this->author_name;
}

// Установка имени автора
void Book::set_author(std::string author_name)
{
    if (this->got_published == true)
        throw std::invalid_argument("Книга была опубликована, вы не можете изменить имя автора\n");
    else if (author_name == "")
    {
        this->author_name = "Undefined";
        return;
    }
    this->author_name = author_name;
}

// Возвращение названия книги
std::string Book::get_name()
{
    return this->book_name;
}

// Установка названия книги
void Book::set_name(std::string book_name)
{
    if (this->got_published == true)
        throw std::invalid_argument("Книга была опубликована, вы не можете изменить ее название\n");
    else if (book_name == "")
    {
        this->book_name = "Undefined";
        return;
    }
    this->book_name = book_name;
}

// Возвращения типа книги
std::string Book::get_type()
{
    return this->type;
}

// Установка типа книги
void Book::set_type(std::string type)
{
    if (this->got_published == true)
        throw std::invalid_argument("Книга была опубликована, вы не можете изменить ее тип\n");
    else if (type != "Electronic" && type != "Hardcover" && type != "Softback" && type != "")
        throw std::invalid_argument("Вы не можете установить этот тип");
    else if (type == "")
    {
        this->type = "Undefined";
        return;
    }
    this->type = type;
}

// Установка размера книги (кол-во глав и страниц)
void Book::set_size(int chapters, int pages)
{
    if (this->got_published == true)
        throw std::invalid_argument("Книга была опубликована, вы не можете изменить ее размер\n");
    else if ((chapters == 0 && pages != 0) || (chapters != 0 && pages == 0))
        throw std::invalid_argument("Кол-во глав и страниц может быть равно нулю только одновременно\n");
    this->chapters_amount = chapters;
    this->pages_amount = pages;
}

// Вычисление среднего кол-ва страниц на главу
double Book::pages_per_chapter()
{
    if (this->chapters_amount != 0)
        return this->pages_amount / this->chapters_amount;
    return 0;
}

// Публикация книги
void Book::publish(std::string publishing_house, int year, long long int ISBN)
{
    if (this->got_published == true)
        throw std::invalid_argument("Книга уже опубликована, вы не можете опубликовать ее еще раз\n");
    else if (publishing_house != "" && year != 0 &&
             ISBN >= 1000000000000 && ISBN <= 9999999999999)
    {
        this->publishing_house = publishing_house;
        this->year = year;
        this->ISBN = ISBN;
        this->got_published = true;
        return;
    }
    else if (publishing_house == "" && year == 0 && ISBN == 0)
    {
        this->publishing_house = "Undefined";
        this->year = year;
        this->ISBN = ISBN;
        return;
    }
    throw std::invalid_argument("Вы не можете опубликовать книгу с такими параметрами\n");
}