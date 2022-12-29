#include "DateTime.h"

void testDateTime() {
    std::cout << "Создание 3-ех объектов класса DateTime с помощью разных конструкторов" << std::endl;
    std::cout << "1-ый объект создаем со своими данными, 2-ой без параметров, 3-ий копируем из первого" << std::endl;
    std::cout << "3-ий объект создаем с помощью оператора new для проверки работоспособности деструктора в будущем:\n";
    DateTime first_date = DateTime(2022, 11, 29, 20, 30);
    DateTime second_date = DateTime();
    DateTime *third_date = new DateTime(first_date);

    std::cout << "\nПроверка правильности вывода данных:" << std::endl;
    first_date.printDateTime();
    second_date.printDateTime();
    third_date->printDateTime();

    std::cout << "\nПроверка работоспособности статического поля счетчика объектов:" << std::endl;
    std::cout << "Сейчас объектов в счетчике: " << DateTime::getObjectsCounter() << std::endl;

    // Проверка работоспособности методов для уменьшения/увеличения полей класса.
    first_date.minusYear();
    first_date.minusMonth();
    first_date.minusDay();
    first_date.minusHour();
    first_date.minusMinute();
    second_date.plusYear();
    second_date.plusMonth();
    second_date.plusDay();
    second_date.plusHour();
    second_date.plusMinute();

    std::cout << "\nПроверка вывода данных после использования методов для изменений некоторых полей" << std::endl;
    std::cout << "В 1-ом объекте все поля уменьшены на 1, во 2-ом - увеличены. 3 без изменений." << std::endl;
    first_date.printDateTime();
    second_date.printDateTime();
    third_date->printDateTime();

    std::cout << "\nУдаление 3-го объекта вручную и проверка работоспособности счетчика объектов:" << std::endl;
    delete third_date;
    std::cout << "Сейчас объектов в счетчике: " << DateTime::getObjectsCounter() << std::endl;

    std::cout << "\nПосле завершения выполнения программы деструкторы для оставшихся объектов должны вызваться сами:\n";
}

int main() {
    testDateTime(); // Вызов тестирующей функции.
    return 0;
}
