#include <iostream>

struct List // Создание нового типа данных
{
    int value;                        // информационная часть
    List *next;                       // служебная часть
    List(int val = 0, List *p = NULL) // конструктор
    {
        value = val;
        next = p;
    }
};

// Включение элемента в начало списка
List *Insert_first(int n, List *head)
{
    List *q = new List(n, head);
    return q;
}

void reverse(List *head)
{
    List *temp = new List;
    List *prev = new List;
    List *current = head;
    while (current != NULL)
    {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    head = prev;
}

// Печать содержимого списка
void Print_list(List *head)
{
    List *p = head;
    puts("\n PRINT LIST");
    if (p == NULL)
        puts("List empty!");
    else
        while (p->next != NULL)
        {
            printf("%d ", p->value);
            p = p->next;
        }
}

int first_appearance(int E, List *head)
{
    List *elem = head;
    int i = 1, counter = 0; // Инициализация переменных для нахождения адреса и счетчика вхождений.
    int first = 0;          // Инициализация переменной для адреса первого появления переменной.

    while (elem->next != NULL) // Итерирование по списку.
    {
        if (elem->value == E)
        {              // Проверка на совпадение элемента списка и переданного числа.
            counter++; // Увеличение счетчика на 1 при совпадении.
            if (first == 0)
                first = i; // Присваивание адреса первого вхождения, если его еще нет.
        }

        // Переход к следующему элементу.
        // Вместе с переходом к следующему адресу.
        elem = elem->next;
        i++;
    }

    // Вывод кол-ва вхождений числа в список.
    // Возвращение адреса первого вхождения.
    std::cout << "Number " << E << " appears " << counter << " times in the list" << std::endl;
    return first;
}

int delete_duplicates(List *head)
{
    List *temp_2, *temp, *elem = head; // Инициализация перменных списков.
    int deleted_counter = 0;           // Инициализация переменной для подсчета удаленных элементов.

    while (elem->next != NULL) // Итерирование по основному списку.
    {
        temp = elem;
        while (temp->next != NULL) // Внутреннее итерирование по списку.
        {
            // Поиск и удаление дубликатов в списке.
            if (elem->value == temp->next->value)
            {
                temp_2 = temp->next;
                temp->next = temp->next->next;
                delete temp_2;
                deleted_counter++; // Увеличение счетчика удаленных элементов.
            }
            else
            {
                temp = temp->next;
            }
        }
        // Переход к следующему элементу для поиска его дубликатов
        elem = elem->next;
    }
    return deleted_counter; // Возвращение кол-ва удаленных элементов.
}

int main()
{
    List *list = new List;

    list = Insert_first(3, list);
    list = Insert_first(3, list);
    list = Insert_first(6, list);
    list = Insert_first(2, list);
    list = Insert_first(3, list);
    list = Insert_first(7, list);
    list = Insert_first(2, list);
    list = Insert_first(4, list);
    list = Insert_first(7, list);
    list = Insert_first(4, list);

    Print_list(list);
    std::cout << std::endl;
    reverse(list);
    Print_list(list);

    // int test = first_appearance(6, list);
    // std::cout << "Address of the first appearance: " << test;

    return 0;
}