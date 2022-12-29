#include "book.h"

int main()
{
    // Инициализация объекта класса книга
    Book book_1 = Book("J.K.Rowling",
                       "Harry Potter and the philosopher's stone",
                       "Hardcover");

    // Проверка работы метода публикации и обработка исключения
    try
    {
        book_1.publish("Scholastic Corporation", 1997, 9783453435773);
    }
    catch (std::length_error)
    {
        std::cout << "Поймано исключение, т.к. в книге нет глав.\n";
    }

    // Инициализация объектов класса глава
    Chapter HP_1 = Chapter("The Boy Who Lived", 28);
    Chapter HP_2 = Chapter("The Vanishing Glass", 33);
    Chapter HP_3 = Chapter("The Letters From No One", 50);

    Chapter exception_test1 = Chapter("The Boy Who Lived", 13);
    Chapter exception_test2 = Chapter("The Keeper of the Keys", 0);

    // Проверка функциональности методов класса книга и обработка исключений
    book_1.add_chapter(HP_1);
    book_1.add_chapter(HP_2);
    book_1.add_chapter(HP_3);
    try
    {
        book_1.add_chapter(exception_test1);
    }
    catch (std::invalid_argument)
    {
        std::cout << "Поймано исключение, т.к. в книге уже есть глава с таким названием.\n";
    }
    book_1.add_chapter(exception_test2);
    try
    {
        book_1.publish("Scholastic Corporation", 1997, 9783453435773);
    }
    catch (std::logic_error)
    {
        std::cout << "Поймано исключение, т.к. в одной из глав книги нет страниц.\n";
    }
    book_1.del_chapter(4);
    book_1.change_chapter(3, "The Letters From No One", 43);
    book_1.print_chapters();
    book_1.publish("Scholastic Corporation", 1997, 9783453435773);

    return 0;
}