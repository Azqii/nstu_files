//
// Created by Dima on 23.11.2025.
//

#ifndef ALGS_LAB_1_HASHTABLE_H
#define ALGS_LAB_1_HASHTABLE_H
#include <vector>
#include <list>
#include <string>
#include <iostream>


template<class T>
class Hashtable {
protected:
    class Node {
    public:
        std::string key;
        T data;
        Node(const std::string& key, const T& data);
    };

    std::vector<std::list<Node>> table;
    size_t capacity;
    size_t size;

    size_t lastHashValue;
    size_t lastProbeCount;

    // Конкатенация битовых образов символов строки -> k'
    size_t keyToNat(const std::string& key) const;
    // Модульная хеш-функция
    size_t hash(const std::string& key) const;

public:
    class Iterator {
    private:
        const Hashtable* parent;
        size_t bucket;
        typename std::list<Node>::iterator it;
        bool ended;

        void moveToNextNonempty();

    public:
        Iterator(const Hashtable* parent, size_t bucket, bool end_flag);
        Node& operator*();
        Node* operator->();
        Iterator& operator++();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;
    Iterator end() const;

    Hashtable(size_t capacity = 101);
    size_t getSize() const;
    size_t getCapacity() const;
    bool isEmpty() const;
    void clear();
    T* find(const std::string& key);
    bool insert(const std::string& key, const T& data);
    bool remove(const std::string& key);
    void show() const;
    size_t getLastHash() const;
    size_t getLastProbeCount() const;
};


template<class T>
Hashtable<T>::Node::Node(const std::string &key, const T &data) {
    this->key = key;
    this->data = data;
}


template<class T>
void Hashtable<T>::Iterator::moveToNextNonempty() {
    while (!this->ended && this->bucket < this->parent->capacity && this->it == this->parent->table[this->bucket].end()) {
        this->bucket++;
        if (this->bucket == this->parent->capacity) {
            this->ended = true;
            return;
        }
        this->it = const_cast<std::list<Node> &>(this->parent->table[this->bucket]).begin();
    }
}


template<class T>
Hashtable<T>::Iterator::Iterator(const Hashtable<T> *parent, size_t bucket, bool end_flag) {
    this->parent = parent;
    this->bucket = bucket;
    this->ended = end_flag;
    if (!this->ended) {
        this->it = const_cast<std::list<Node> &>(this->parent->table[this->bucket]).begin();
        this->moveToNextNonempty();
    }
}


template<class T>
typename Hashtable<T>::Node &Hashtable<T>::Iterator::operator*() {
    return *it;
}


template<class T>
typename Hashtable<T>::Node *Hashtable<T>::Iterator::operator->() {
    return &(*it);
}


template<class T>
typename Hashtable<T>::Iterator &Hashtable<T>::Iterator::operator++() {
    if (this->ended) {
        return *this;
    }
    ++this->it;
    this->moveToNextNonempty();
    return *this;
}


template<class T>
bool Hashtable<T>::Iterator::operator==(const Hashtable<T>::Iterator &other) const {
    if (this->ended && other.ended) {
        return true;
    }
    return (
            this->parent == other.parent &&
            this->bucket == other.bucket &&
            this->it == other.it &&
            this->ended == other.ended
    );
}


template<class T>
bool Hashtable<T>::Iterator::operator!=(const Hashtable<T>::Iterator &other) const {
    return !(*this == other);
}


template<class T>
typename Hashtable<T>::Iterator Hashtable<T>::begin() const {
    for (size_t i = 0; i < this->capacity; i++)
        if (!this->table[i].empty())
            return Iterator(this, i, false);
    return this->end();
}


template<class T>
typename Hashtable<T>::Iterator Hashtable<T>::end() const {
    return Iterator(this, this->capacity, true);
}


template<class T>
Hashtable<T>::Hashtable(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->lastHashValue = 0;
    this->lastProbeCount = 0;

    this->table.resize(this->capacity);
}


template<class T>
size_t Hashtable<T>::getSize() const {
    return this->size;
}


template<class T>
size_t Hashtable<T>::getCapacity() const {
    return this->capacity;
}


template<class T>
bool Hashtable<T>::isEmpty() const {
    return this->size == 0;
}


template<class T>
void Hashtable<T>::clear() {
    for (auto& lst : this->table) {
        lst.clear();
    }
    this->size = 0;
    this->lastHashValue = 0;
    this->lastProbeCount = 0;
}


template<class T>
size_t Hashtable<T>::keyToNat(const std::string &key) const {
    size_t acc = 0;
    for (unsigned char c : key) {
        acc = (acc << 8) | c;
    }
    return acc;
}


template<class T>
size_t Hashtable<T>::hash(const std::string &key) const {
    return this->keyToNat(key) % this->capacity;
}


template<class T>
T* Hashtable<T>::find(const std::string &key) {
    this->lastProbeCount = 0;
    this->lastHashValue = this->hash(key);
    auto& lst = this->table[this->lastHashValue];

    for (auto& node : lst) {
        this->lastProbeCount++;
        if (node.key == key) {
            return &node.data;
        }
    }
    return nullptr;
}


template<class T>
bool Hashtable<T>::insert(const std::string &key, const T &data) {
    this->lastProbeCount = 0;
    this->lastHashValue = this->hash(key);
    auto& lst = this->table[this->lastHashValue];

    for (auto& node : lst) {
        this->lastProbeCount++;
        if (node.key == key) {
            return false;
        }
    }

    lst.emplace_front(key, data);
    this->lastProbeCount++;
    this->size++;
    return true;
}


template<class T>
bool Hashtable<T>::remove(const std::string &key) {
    this->lastProbeCount = 0;
    this->lastHashValue = this->hash(key);

    auto& lst = this->table[this->lastHashValue];
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        this->lastProbeCount++;
        if (it->key == key) {
            lst.erase(it);
            this->size--;
            return true;
        }
    }
    return false;
}


template<class T>
void Hashtable<T>::show() const {
    for (size_t i = 0; i < this->capacity; i++) {
        std::cout << i << ":";
        for (const auto& node : this->table[i])
            std::cout << " [" << node.key << "]";
        std::cout << std::endl;
    }
}


template<class T>
size_t Hashtable<T>::getLastHash() const {
    return this->lastHashValue;
}


template<class T>
size_t Hashtable<T>::getLastProbeCount() const {
    return this->lastProbeCount;
}


#endif //ALGS_LAB_1_HASHTABLE_H
