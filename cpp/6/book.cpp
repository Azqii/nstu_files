#include "book.h"

// Конструктор с параметрами
Book::Book(std::string author_name,
           std::string book_name,
           std::string type)
{
    this->got_published = false;
    this->set_author(author_name);
    this->set_name(book_name);
    this->set_type(type);
}

// Конструктор без параметров
Book::Book() : Book("", "", "") {}

// Возвращение имени автора
std::string Book::get_author()
{
    return this->author_name;
}

// Установка имени автора
void Book::set_author(std::string author_name)
{
    if (this->got_published == true)
        throw std::logic_error("Книга уже опубликована, вы не можете изменить имя автора\n");
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
        throw std::logic_error("Книга уже опубликована, вы не можете изменить ее название\n");
    else if (book_name == "")
    {
        this->book_name = "Undefined";
        return;
    }
    this->book_name = book_name;
}

// Возвращение типа книги
std::string Book::get_type()
{
    return this->type;
}

// Установка типа книги
void Book::set_type(std::string type)
{
    if (this->got_published == true)
        throw std::logic_error("Книга уже опубликована, вы не можете изменить ее тип\n");
    else if (type != "Electronic" && type != "Hardcover" && type != "Softback" && type != "")
        throw std::invalid_argument("Вы не можете установить такой тип");
    else if (type == "")
    {
        this->type = "Undefined";
        return;
    }
    this->type = type;
}

// Публикация книги
void Book::publish(std::string publishing_house, int year, long long int ISBN)
{
    if (this->got_published == true)
        throw std::logic_error("Книга уже опубликована, вы не можете опубликовать ее еще раз\n");

    if (this->chapters.empty())
        throw std::length_error("Вы не можете публиковать книгу без глав");

    for (Chapter c : this->chapters)
    {
        if (c.get_pages() == 0)
            throw std::logic_error("Вы не можете публиковать книгу, если в какой-то из глав нет страниц");
    }

    if (publishing_house != "" && year != 0 &&
        ISBN >= 1000000000000 && ISBN <= 9999999999999)
    {
        this->publishing_house = publishing_house;
        this->year = year;
        this->ISBN = ISBN;
        this->got_published = true;
        return;
    }
    throw std::invalid_argument("Вы не можете опубликовать книгу с этими параметрами\n");
}

// Добавление главы в книгу
void Book::add_chapter(Chapter chapter)
{
    if (this->got_published == true)
        throw std::logic_error("Книга уже опубликована, вы не можете добавить главу\n");
    for (Chapter c : this->chapters)
    {
        if (chapter.get_name() == c.get_name())
            throw std::invalid_argument("У этой книги уже есть глава с таким названием\n");
    }
    this->chapters.push_back(chapter);
}

// Удаление главы из книги
void Book::del_chapter(int number)
{
    if (this->got_published == true)
        throw std::logic_error("Книга уже опубликована, вы не можете удалять главы\n");
    number = number - 1;
    if (this->chapters.size() < number)
        throw std::out_of_range("Такой главы нет в книге\n");
    this->chapters.erase(this->chapters.begin() + number);
}

// Изменение имени и кол-ва страниц в главе из книги
void Book::change_chapter(int number, std::string new_name, int new_pages)
{
    if (this->got_published == true)
        throw std::logic_error("Книга уже опубликована, вы не можете изменять информацию о главах\n");
    number = number - 1;
    if (this->chapters.size() < number)
        throw std::out_of_range("Такой главы нет в книге\n");
    this->chapters[number].set_name(new_name);
    this->chapters[number].set_pages(new_pages);
}

// Распечатка информации о главах книги
void Book::print_chapters()
{
    int i = 1;
    for (Chapter c : this->chapters)
    {
        std::cout << "Глава №" << i << " " << c.get_name() << " | Кол-во страниц: " << c.get_pages() << std::endl;
        i++;
    }
}