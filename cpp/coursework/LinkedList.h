//
// Created by dima on 08.01.23.
//

#ifndef CRS_LINKEDLIST_H
#define CRS_LINKEDLIST_H

#include <iostream>


template<class T>
class LinkedList { // Двусвязный циклический список
private:
    struct Node { // Элемент списка;
        T *data;
        Node *prev;
        Node *next;

        explicit Node(T *data);
    };

    Node
            *head, // Первый элемент
            *tail; // Последний элемент

    int
            size; // Размер списка

private:
    Node *getElement(int position);


public:
    LinkedList(); // Конструктор по умолчанию

    ~LinkedList(); // Деструктор

    void pushFront(T *data); // Добавление элемента в начало

    void pushBack(T *data); // Добавление элемента в конец

    void push(T *data, int position); // Добавление элемента по логическому номеру

    T *popFront(); // Извлечение первого элемента

    T *popBack(); // Извлечение последнего элемента

    T *pop(int position); // Извлечение элемента по логическому номеру

    T *peek(int position); // Извлечение по логическому номеру без удаления

    void sort(); // Сортировка списка

    int getSize(); // Возвращает размер списка

    void printList(); // Распечатывает список
};

template<class T>
typename LinkedList<T>::Node *LinkedList<T>::getElement(int position) {
    if (position < 1 || position > this->size)
        throw std::length_error("Данная позиция за пределами списка");

    Node *elem = this->head;

    for (int i = 1; i < position; i++)
        elem = elem->next;

    return elem;
}

template<class T>
LinkedList<T>::Node::Node(T *data) {
    this->data = data;
    this->prev = this->next = nullptr;
}

template<class T>
LinkedList<T>::LinkedList() {
    this->head = this->tail = nullptr;
    this->size = 0;
}

template<class T>
LinkedList<T>::~LinkedList() {
    for (int i = 0; i < this->size; i++) {
        Node *toDelete = this->head;
        this->head = this->head->next;
        delete toDelete;
    }
}

template<class T>
void LinkedList<T>::pushFront(T *data) {
    Node *elem = new Node(data);
    elem->next = this->head;

    if (this->head != nullptr)
        this->head->prev = elem;
    if (this->tail == nullptr)
        this->tail = elem;

    this->head = elem;
    this->head->prev = this->tail;
    this->tail->next = this->head;

    this->size++;
}

template<class T>
void LinkedList<T>::pushBack(T *data) {
    Node *elem = new Node(data);
    elem->prev = this->tail;

    if (this->tail != nullptr)
        this->tail->next = elem;
    if (this->head == nullptr)
        this->head = elem;

    this->tail = elem;
    this->tail->next = this->head;
    this->head->prev = this->tail;

    this->size++;
}

template<class T>
void LinkedList<T>::push(T *data, int position) {
    if (position == 1) {
        this->pushFront(data);
        return;
    } else if (position == this->size + 1) {
        this->pushBack(data);
        return;
    }

    Node *elem = this->getElement(position);
    Node *newElem = new Node(data);

    newElem->next = elem;
    newElem->prev = elem->prev;
    elem->prev->next = newElem;
    elem->prev = newElem;

    this->size++;
}


template<class T>
T *LinkedList<T>::popFront() {
    if (this->head == nullptr)
        throw std::length_error("Список пуст");

    T *toReturn = this->head->data;

    if (this->size == 1) {
        delete this->head;
        this->head = this->tail = nullptr;
        this->size--;
        return toReturn;
    }

    Node *elem = this->head->next;
    delete this->head;
    this->head = elem;
    this->head->prev = this->tail;
    this->tail->next = this->head;

    this->size--;
    return toReturn;
}

template<class T>
T *LinkedList<T>::popBack() {
    if (this->tail == nullptr)
        throw std::length_error("Список пуст");

    T *toReturn = this->tail->data;

    if (this->size == 1) {
        delete this->tail;
        this->tail = this->head = nullptr;
        this->size--;
        return toReturn;
    }

    Node *elem = this->tail->prev;
    delete this->tail;
    this->tail = elem;
    this->tail->next = this->head;
    this->head->prev = this->tail;

    this->size--;
    return toReturn;
}

template<class T>
T *LinkedList<T>::pop(int position) {
    if (position == 1)
        return this->popFront();
    else if (position == this->size)
        return this->popBack();

    Node *deleteElem = this->getElement(position);
    T *toReturn = deleteElem->data;
    deleteElem->next->prev = deleteElem->prev;
    deleteElem->prev->next = deleteElem->next;
    delete deleteElem;

    this->size--;
    return toReturn;
}

template<class T>
T *LinkedList<T>::peek(int position) {
    if (position == 1)
        return this->head->data;
    else if (position == size)
        return this->tail->data;

    return this->getElement(position)->data;
}

template<class T>
void LinkedList<T>::sort() {
    Node *currentElement, *place, *prevPlace;
    Node *newHead = nullptr;

    for (int i = 0; i < this->size; i++) {
        currentElement = this->head;
        this->head = this->head->next;

        // Поиск места вставки элемента
        for (place = newHead, prevPlace = nullptr;
             place != nullptr && *currentElement->data > *place->data;
             prevPlace = place, place = place->next);

        if (prevPlace == nullptr) { // Вставка на первую позицию
            currentElement->next = newHead;
            if (newHead != nullptr)
                newHead->prev = currentElement;
            newHead = currentElement;
        } else { // Вставка в середину или конец
            currentElement->next = place;
            if (place != nullptr) {
                place->prev = currentElement;
                if (place->next == nullptr)
                    this->tail = place;
            } else
                this->tail = currentElement;
            currentElement->prev = prevPlace;
            prevPlace->next = currentElement;
        }
    }

    this->head = newHead;
    this->tail->next = this->head;
    this->head->prev = this->tail;
}

template<class T>
int LinkedList<T>::getSize() {
    return this->size;
}

template<class T>
void LinkedList<T>::printList() {
    Node *toPrint = this->head;
    for (int i = 1; i <= this->size; i++) {
        std::cout << "#" << i << " | " << *toPrint->data << std::endl;
        toPrint = toPrint->next;
    }
}


#endif //CRS_LINKEDLIST_H
