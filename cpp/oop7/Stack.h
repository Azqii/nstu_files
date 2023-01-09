//
// Created by dima on 05.01.23.
//

#ifndef OOP7_STACK_H
#define OOP7_STACK_H

#include "DateTime.h"


template <class T>
class Stack {
private:
    struct Node { // Элемент стека
        T *data;
        Node *next;

        Node(T *data, Node *next);
    };

    Node *top; // Верхний элемент стека

    int size; // Размер стека

public:
    Stack(); // Конструктор по умолчанию

    explicit Stack(T *data); // Конструктор с параметром

    ~Stack(); // Деструктор

    bool isEmpty() const; // Метод проверяющий стек на пустоту

    void push(T *data); // Метод для добавления верхнего элемента

    T *pop(); // Метод, возвращающий и удаляющий верхний элемент

    T *peek() const; // Метод, возвращающий верхний элемент

    int getSize() const; // Геттер поля размера
};


template <class T>
Stack<T>::Node::Node(T *data, Stack::Node *next) {
    this->data = data;
    this->next = next;
}

template <class T>
Stack<T>::Stack() {
    this->top = nullptr;
    this->size = 0;
}

template <class T>
Stack<T>::Stack(T *data) {
    this->top = new Node(data, nullptr);
    this->size = 1;
}

template <class T>
Stack<T>::~Stack() {
    while (!this->isEmpty()) {
        Node *toDelete = this->top;
        this->top = this->top->next;
        delete toDelete;
    }
}

template <class T>
bool Stack<T>::isEmpty() const {
    return this->top == nullptr;
}

template <class T>
void Stack<T>::push(T *data) {
    Node *newTop = new Node(data, this->top);
    this->top = newTop;
    this->size++;
}

template <class T>
T *Stack<T>::pop() {
    if (this->isEmpty())
        throw std::range_error("Стек пуст");

    Node *prevTop = this->top;
    T *prevTopData = this->top->data;
    this->top = this->top->next;
    delete prevTop;
    this->size--;

    return prevTopData;
}

template <class T>
T *Stack<T>::peek() const {
    return this->top->data;
}

template <class T>
int Stack<T>::getSize() const {
    return this->size;
}


#endif //OOP7_STACK_H
