//
// Created by Dima on 23.11.2025.
//

#ifndef ALGS_LAB_1_HASHTABLE_H
#define ALGS_LAB_1_HASHTABLE_H
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>


template<class T>
class Hashtable {
protected:
    class Node {
    public:
        std::string key;
        T data;
        Node(const std::string& key, const T& data);
    };

    static std::vector<int> MersenneNumbers;

    std::vector<std::list<Node>> table;
    size_t capacity;
    size_t size;

    size_t lastHashValue;
    size_t lastProbeCount;

    int findSuitableMersenneNumber(int number);
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
        T& operator*();
        T* operator->();
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
    size_t getBucketSize(size_t index) const;
};


template<class T>
std::vector<int> Hashtable<T>::MersenneNumbers = {
        7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521, 131071,
        262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393
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
T &Hashtable<T>::Iterator::operator*() {
    return this->it->data;
}


template<class T>
T *Hashtable<T>::Iterator::operator->() {
    return &(this->it->data);
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
int Hashtable<T>::findSuitableMersenneNumber(int number) {
    for (number; number >= 7; number--) {
        if (std::find(MersenneNumbers.begin(), MersenneNumbers.end(), number) != MersenneNumbers.end()) {
            return number;
        }
    }
    throw std::invalid_argument("Нет подходящего числа Мерсенне");
}


template<class T>
Hashtable<T>::Hashtable(size_t capacity) {
    this->capacity = this->findSuitableMersenneNumber(capacity / 2);
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
    size_t k = 0, kk = 0;
    for (int i = 0; i < key.length(); i++) {
        if ((i + 1) % 6 == 0) {
            kk = kk ^ k;
            k = 0;
        }
        k = k << 5;
        k = k | key[i] - 'a' + 1;
    }
    kk = kk ^ k;
    return kk;
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


template<class T>
size_t Hashtable<T>::getBucketSize(size_t index) const {
    if (index >= this->capacity) {
        return 0;
    }
    return this->table[index].size();
}


#endif //ALGS_LAB_1_HASHTABLE_H
