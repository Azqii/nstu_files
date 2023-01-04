#include "Time.h"
#include "Stack.h"


void testExceptions() {
    // Тестирование исключительных ситуаций
    try { DateTime(2023, 13, 2, 24, 10); }
    catch (std::invalid_argument &) {
        std::cout << "Исключение поймано из-за ввода несуществующей даты." << std::endl;
    }

    std::cout << "\n*******************************************************************************\n" << std::endl;

    try {
        DateTime date;
        date.plusDay();
    }
    catch (std::invalid_argument &) {
        std::cout << "Исключение поймано из-за того, что мы пытаемся установить день у неустановленного месяца"
                  << std::endl;
    }

    std::cout << "\n*******************************************************************************\n" << std::endl;

    try {
        Time time;
        time.changeTime(13, 00);
    }
    catch (std::invalid_argument &) {
        std::cout << "Исключение поймано из-за попытки изменить время более чем на 12 часов" << std::endl;
    }

    std::cout << "\n*******************************************************************************\n" << std::endl;

    try {
        Stack stack;
        stack.pop();
    }
    catch (std::range_error &) {
        std::cout << "Исключение поймано из-за попытки вытащить элемент из пустого стека" << std::endl;
    }
}

int main() {
    testExceptions();
    return 0;
}
