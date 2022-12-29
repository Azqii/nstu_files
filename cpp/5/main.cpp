#include "book.h"

int main()
{
    // Инициализация первого объекта класса книга
    Book book_1 = Book("J.K.Rowling",
                       "Harry Potter and the philosopher's stone",
                       "Scholastic Corporation",
                       1997,
                       223,
                       17,
                       "Hardcover",
                       9780590353403);
    // Инициализация второго объекта класса книга
    Book book_2 = Book();

    // Проверка работоспособности методов класса книга
    book_2.set_author("S.King");
    std::cout << "Автор первой книги: " << book_1.get_author();
    std::cout << "\nАвтор второй книги: " << book_2.get_author();

    book_2.set_name("It");
    std::cout << "\nНазвание второй книги: " << book_2.get_name();

    book_2.set_size(0, 0);
    std::cout << "\nСреднее кол-во страниц на главу первой книги: ~" << book_1.pages_per_chapter();
    std::cout << "\nСреднее кол-во страниц на главу второй книги: ~" << book_2.pages_per_chapter();

    book_2.publish("Viking", 1986, 9783453435773);

    // Намеренный вызов исключения
    std::cout << "\n\nЗдесь должно быть исключение:\n";
    book_2.set_author("A.S.Pushkin");
    return 0;
}