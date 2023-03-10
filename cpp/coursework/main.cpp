#include "Rental.h"
#include "LinkedList.h"


void fillList(LinkedList<Rental> &list) { // Наполнение листа элементами в начале выполнения программы
    list.pushBack(new Rental("Bike", "Dima", 1000, DateTime(2022, 1, 9, 20, 0)));
    list.pushBack(new Rental("Car", "Vova", 2000, DateTime(2022, 1, 10, 19, 30)));
    list.pushBack(new Rental("Room", "Danil", 1500, DateTime(2022, 1, 8, 20, 0)));
}

void addElem(LinkedList<Rental> &list) { // Добавление элемента с клавиатуры
    std::cout << "Введите через пробел название предмета, имя арендатора, цену "
              << "и год, месяц, день, часы и минуты выдачи (тоже через пробел):" << std::endl;

    DateTime receiveTime;
    std::string object, person;
    int price;
    std::cin >> object >> person >> price >> receiveTime;

    auto elem = new Rental(object.c_str(), person.c_str(), price, receiveTime);
    list.pushBack(elem);
}

void setReturn(LinkedList<Rental> &list) { // Назначение даты возврата
    std::cout << "Введите логический номер элемента:" << std::endl;
    int number;
    std::cin >> number;

    Rental *elem = list.peek(number);
    std::cout << "Введите год, месяц, день, часы и минуты возврата через пробел:" << std::endl;
    DateTime returnTime;
    std::cin >> returnTime;

    try { elem->setReturnTime(returnTime); }
    catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
}

void delElem(LinkedList<Rental> &list) { // Удаление элемента из списка
    std::cout << "Введите логический номер элемента:" << std::endl;
    int number;
    std::cin >> number;

    Rental *elem = list.pop(number);
    std::cout << *elem << " удален" << std::endl;
    delete elem;
    std::cout << "test";
}

void printElem(LinkedList<Rental> &list) { // Вывод на экран отдельного элемента из списка
    std::cout << "Введите логический номер элемента:" << std::endl;
    int number;
    std::cin >> number;

    std::cout << *list.peek(number) << std::endl;
}

int calculateProfit(LinkedList<Rental> &list) { // Подсчет дохода за заданный год/месяц
    std::cout << "Введите год и номер месяца через пробел:" << std::endl;
    int year, month, profit = 0;
    Rental *elem;

    std::cin >> year >> month;
    for (int i = 1; i <= list.getSize(); i++) {
        elem = list.peek(i);
        if (elem->getReceiveTime().getYear() == year && elem->getReceiveTime().getMonth() == month)
            try { profit += elem->calculateOverallPrice(); }
            catch (std::logic_error &) {}
    }

    return profit;
}

void fileWrite(LinkedList<Rental> &list) { // Запись в файл.
    std::cout << "Введите название файла:" << std::endl;
    std::string path;
    std::cin >> path;

    Rental *elem;
    std::fstream fout;
    fout.open(path, std::fstream::out);

    if (fout.is_open()) {
        for (int i = 1; i <= list.getSize(); i++) {
            elem = list.peek(i);
            elem->binWrite(fout);
        }
        fout.close();
    }
}

void fileLoad(LinkedList<Rental> &list) { // Загрузка из файла.
    std::cout << "Введите название файла:" << std::endl;
    std::string path;
    std::cin >> path;
    std::cout << "Введите количество элементов для загрузки:" << std::endl;
    int elementsNumber;
    std::cin >> elementsNumber;


    std::fstream fin;
    fin.open(path, std::fstream::in);

    if (fin.is_open()) {
        for (int i = 0; i < elementsNumber; i++) {
            auto *elem = new Rental;
            elem->binRead(fin);
            list.pushBack(elem);
        }
        fin.close();
    }
}

void menu(LinkedList<Rental> &list) { // Вывод меню
    int choice = -1;

    while (choice != 0) {
        std::cout << std::endl << "Выберите один из пунктов:" << std::endl
                  << "1. Просмотреть все записи в списке." << std::endl
                  << "2. Добавить новую запись в список." << std::endl
                  << "3. Назначить одной из записей день возврата." << std::endl
                  << "4. Удалить запись из списка." << std::endl
                  << "5. Посмотреть запись из списка." << std::endl
                  << "6. Отсортировать список." << std::endl
                  << "7. Подсчитать доход за заданный год/месяц." << std::endl
                  << "8. Записать данные в файл" << std::endl
                  << "9. Загрузить данные из файла" << std::endl << std::endl
                  << "0. Выйти" << std::endl << std::endl;

        std::cin >> choice;

        switch (choice) {
            case 1:
                list.printList();
                break;
            case 2:
                addElem(list);
                break;
            case 3:
                setReturn(list);
                break;
            case 4:
                delElem(list);
                break;
            case 5:
                printElem(list);
                break;
            case 6:
                list.sort();
                break;
            case 7:
                std::cout << calculateProfit(list) << " Рублей" << std::endl;
                break;
            case 8:
                fileWrite(list);
                break;
            case 9:
                fileLoad(list);
                break;
            case 0:
                return;
            default:
                std::cout << "Такого пункта не существует." << std::endl;
                break;
        }
    }
}

int main() {
    LinkedList<Rental> list;

    fillList(list);
    menu(list);

    return 0;
}
