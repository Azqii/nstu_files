#include <iostream>
#include <fstream>
#include <string>

struct List // Создание нового типа данных
{
    int value, amount; // информационная часть
    List *next; // служебная часть
    List(int val = 0, int amnt = 1, List *p = NULL) // конструктор
    {
        value = val;
        amount = amnt;
        next = p;
    }
};

// Включение элемента в начало списка
List *Insert_first(int n, List *head, int amount = 1) {
    List *q = new List(n, amount, head);
    return q;
}

// Распечатка списка.
void Print_list(List *head) {
    List *p = head;
    puts("PRINT LIST");
    if (p == NULL)
        puts("List empty!");
    else
        while (p->next != NULL) {
            std::cout << p->value << "*" << p->amount << " ";
            p = p->next;
        }
}

// Распечатка элементов списка, которые повторяются.
void Print_duplicated_list(List *head) {
    List *p = head;
    puts("PRINT LIST (only duplicated elements)");
    if (p == NULL)
        puts("List empty!");
    else
        while (p->next != NULL) {
            if (p->amount > 1)
                std::cout << p->value << "*" << p->amount << " ";
            p = p->next;
        }
}

// Считывание чисел с клавиатуры в файл.
void enter_numbers(std::string filename) {
    std::ofstream file(filename);
    int number;
    std::cout << "Enter the numbers (0 to stop): ";
    while (true) {
        std::cin >> number;
        if (number == 0)
            break;
        file << number << " ";
    }
    file.close();
}

// Считывание чисел из файла в список.
List *get_numbers(std::string filename) {
    List *temp_list = new List;
    int number;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File not found";
        return temp_list;
    }
// Проход по числам из файла и записывание их в список.
    while (file >> number)
        temp_list = Insert_first(number, temp_list);
    file.close();
    return temp_list;
}

// Слияние одиночных элементов списка
List *merge(List *head) {
    List *temp_2, *temp, *elem = head; // Инициализация перменных временных списков.
    List *result_list = new List; // Инициализация переменной финального списка.
    while (elem->next != NULL) // Итерирование по основному списку.
    {
        temp = elem;
        int counter = 1; // Инициализация счетчика числа.
        while (temp->next != NULL) // Внутреннее итерирование по списку.
        {
// Поиск и слияние дубликатов в списке.
            if (elem->value == temp->next->value) {
                temp_2 = temp->next;
                temp->next = temp->next->next;
                delete temp_2;
                counter++; // Увеличение счетчика слившихся чисел.
            } else {
                temp = temp->next;
            }
        }
        result_list = Insert_first(elem->value, result_list,
                                   counter);
// Переход к следующему элементу для поиска его дубликатов.
        elem = elem->next;
    }
    return result_list;
}

// Сортировка пузырьком списка(неэффективно, но легко и понятно)
List *sort_list(List *head) {
    List *temp, *temp_2, *elem = head;
    List *result_list = new List;
    while (elem->next != NULL) {
        temp = elem;
        while (temp->next != NULL) {
            if (elem->value < temp->value) {
                temp_2->value = elem->value;
                temp_2->amount = elem->amount;
                elem->value = temp->value;
                elem->amount = temp->amount;
                temp->value = temp_2->value;
                temp->amount = temp_2->amount;
            }
            temp = temp->next;
        }
        result_list = Insert_first(elem->value, result_list,
                                   elem->amount);
        elem = elem->next;
    }
    return result_list;
}

int main() {
    List *list = new List;
    enter_numbers("text.txt"); // Вызов функции ввода чисел с клавиатуры в файл.
    list = get_numbers("text.txt"); // Вызов функции записи чисел из файла в список.
    std::cout << "\nOriginal list:\n";
    Print_list(list);
    list = merge(list); // Вызов функции слияния повторяющихся чисел.
    std::cout << "\n\nMerged list:\n";
    Print_list(list);
    list = sort_list(list); // Вызов функции соритровки чисел в списке.
    std::cout << "\n\nSorted list:\n";
    Print_duplicated_list(list); // Вызов функции распечатки чисел, встречающихся > 1 раза.
    return 0;
}