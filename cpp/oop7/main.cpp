#include "Stack.h"


void testTemplates() {
    // Объявление стеков с разными хранимыми в них объектами
    Stack<DateTime> datetimeStack;
    Stack<int> intStack;
    Stack<float> floatStack;

    // Наполнение стеков
    datetimeStack.push(new DateTime(2000, 12, 20, 20, 20));
    intStack.push(new int(2));
    floatStack.push(new float(2.2));

    // Проверка работоспособности
    std::cout << "Объект в datetimeStack: (" << *datetimeStack.pop() << ")" << std::endl;
    std::cout << "Объект в intStack: (" << *intStack.pop() << ")" << std::endl;
    std::cout << "Объект в floatStack: (" << *floatStack.pop() << ")" << std::endl;
}

int main() {
    testTemplates();
    return 0;
}
