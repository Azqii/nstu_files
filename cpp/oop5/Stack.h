//
// Created by dima on 04.01.23.
//

#ifndef OOP5_STACK_H
#define OOP5_STACK_H

#include "DateTime.h"


class Stack {
private:
    struct Node {
        DateTime *data;
        Node *next;

        Node(DateTime *data, Node *next);
    };

    Node *top;

    int size;

public:
    Stack();

    explicit Stack(DateTime *data);

    ~Stack();

    bool isEmpty() const;

    void push(DateTime *data);

    DateTime *pop();

    DateTime *peek() const;

    int getSize() const;
};


#endif //OOP5_STACK_H
