#include "Stack.h"
#include "PlannedEvent.h"
#include "Time.h"


void testFunc() {
    // Наполняем стек объектами родственных классов
    Stack stack = Stack(new DateTime(2020, 5, 12, 20, 30));
    stack.push(new PlannedEvent(2012, 5, 10, 14, 20, "testEvent"));
    stack.push(new Time(2018, 4, 4, 18, 40));

    /*
     * Демонстрируем полиморфическое поведение классов с помощью оператора приведения к типу char*, который переназначен
     * в обоих классах-потомках.
    */
    for (int i = stack.getSize(); i > 0; i--) {
        char *test = *stack.pop();
        std::cout << test << std::endl;
    }
}

int main() {
    testFunc();
    return 0;
}
