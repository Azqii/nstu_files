#ifndef MODELING_KR_LIST_H
#define MODELING_KR_LIST_H

#include <cstddef>

template <class Type>
class ListNode {
private:
    ListNode<Type>* next;
    Type* data;
public:
    ListNode(Type* d, ListNode<Type>* n);
    ~ListNode();
    Type* Data();
    ListNode<Type>* Next();
    void PutNext(ListNode<Type>* n);
    void Print();
};

template <class Type>
ListNode<Type>::ListNode(Type* d, ListNode<Type>* n) : next(n), data(d) {
}

template <class Type>
ListNode<Type>::~ListNode() {
    delete data;
}

template <class Type>
Type* ListNode<Type>::Data() {
    return data;
}

template <class Type>
ListNode<Type>* ListNode<Type>::Next() {
    return next;
}

template <class Type>
void ListNode<Type>::PutNext(ListNode<Type>* n) {
    next = n;
}

template <class Type>
void ListNode<Type>::Print() {
    data->Print();
}

template <class Type>
void ListAdd(ListNode<Type>* head, ListNode<Type>* li) {
    ListNode<Type>* old, * v;
    for (v = head; v != NULL; v = v->Next())
        old = v;
    old->PutNext(li);
}

template <class Type>
ListNode<Type>* ListDelete(ListNode<Type>* head, ListNode<Type>* li) {
    ListNode<Type>* old, * o1;
    if (li == head) {
        o1 = head->Next();
        delete li;
        return o1;
    }
    for (ListNode<Type>* v = head; v != li; v = v->Next())
        old = v;
    o1 = li->Next();
    old->PutNext(o1);
    delete li;
    return head;
}

template <class Type>
void ListPrint(ListNode<Type>* head) {
    for (ListNode<Type>* v = head; v != NULL; v = v->Next())
        v->Print();
}

template <class Type>
int ListCount(ListNode<Type>* head) {
    int i = 0;
    for (ListNode<Type>* v = head; v != NULL; v = v->Next()) {
        v->Print();
        i++;
    }
    return i;
}

#endif //MODELING_KR_LIST_H
