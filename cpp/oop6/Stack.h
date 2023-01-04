//
// Created by dima on 04.01.23.
//

#ifndef OOP6_STACK_H
#define OOP6_STACK_H

#include "DateTime.h"


class Stack {
private:
    struct Node { // Элемент стека
        DateTime *data;
        Node *next;

        Node(DateTime *data, Node *next);
    };

    Node *top; // Верхний элемент стека

    int size; // Размер стека

public:
    Stack(); // Конструктор по умолчанию

    explicit Stack(DateTime *data); // Конструктор с параметром

    ~Stack(); // Деструктор

    bool isEmpty() const; // Метод проверяющий стек на пустоту

    void push(DateTime *data); // Метод для добавления верхнего элемента

    DateTime *pop(); // Метод, возвращающий и удаляющий верхний элемент

    DateTime *peek() const; // Метод, возвращающий верхний элемент

    int getSize() const; // Геттер поля размера
};


#endif //OOP6_STACK_H
