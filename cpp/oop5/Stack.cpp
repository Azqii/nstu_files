//
// Created by dima on 04.01.23.
//

#include "Stack.h"

Stack::Node::Node(DateTime *data, Stack::Node *next) {
    this->data = data;
    this->next = next;
}

Stack::Stack() {
    this->top = nullptr;
    this->size = 0;
}

Stack::Stack(DateTime *data) {
    this->top = new Node(data, nullptr);
    this->size = 1;
}

Stack::~Stack() {
    while (!this->isEmpty()) {
        Node *toDelete = this->top;
        this->top = this->top->next;
        delete toDelete;
    }
}

bool Stack::isEmpty() const {
    return this->top == nullptr;
}

void Stack::push(DateTime *data) {
    Node *newTop = new Node(data, this->top);
    this->top = newTop;
    this->size++;
}

DateTime *Stack::pop() {
    if (this->isEmpty())
        throw std::range_error("Стек пуст");

    Node *prevTop = this->top;
    DateTime *prevTopData = this->top->data;
    this->top = this->top->next;
    delete prevTop;
    this->size--;

    return prevTopData;
}

DateTime *Stack::peek() const {
    return this->top->data;
}

int Stack::getSize() const {
    return this->size;
}


