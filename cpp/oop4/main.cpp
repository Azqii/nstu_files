#include "Time.h"
#include "PlannedEvent.h"


void testClasses() {
    // Инициализация объекта класса Time
    Time time = Time(2023, 3, 1, 20, 30);

    // Тестирование функционала объекта класса Time
    std::cout << "Изначальное время: ";
    time.printTime();
    time.changeTime(10, 30);
    std::cout << "Время после изменения: ";
    time.printTime();

    std::cout << "\n*******************************************************************************\n" << std::endl;

    // Объявление объекта класса PlannedEvent
    PlannedEvent event;

    // Тестирование функционала объекта класса PlannedEvent
    std::cout << "Введите год, месяц, день, час, минуту и название мероприятия через пробел:" << std::endl;
    std::cin >> event;
    std::cout << "Изначальные данные мероприятия: " << event << std::endl;
    event.setEventName("new_event_name");
    std::cout << "Данные мероприятия после изменения его названия: " << event << std::endl;

}

int main() {
    testClasses();
    return 0;
}
