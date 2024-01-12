//
// Created by DimaWin on 05.01.2024.
//

#ifndef TREE_H
#define TREE_H


template <class K, class V>
class Tree {
protected:
    class Node {
    public:
        K key;
        V value;
        Node *left, *right;

        Node(K key, V value);
    };

    int countAllSubNodes(Node* node) const;
    void removeAllSubNodes(Node*& node);
    void printAllKeysByScheme(Node* node) const;
    void showKeyWithIndent(Node* node, int level) const;

    Node* root;

public:
    class Iterator {
    private:
        Tree* ptr;
        Node* current;

        Node* getNextParent(Node* fromNode);

    public:
        explicit Iterator(Tree* tree);
        K& operator *();
        Iterator& operator ++();
        bool operator ==(const Iterator&);
    };

    Iterator begin();
    Iterator end();

    Tree();
    int getSize() const;
    void clear();
    bool isEmtpy() const;
    V search(K key) const;
    void insert(K key, V value);
    void remove(K key);
    void printKeysByScheme() const;
    void printStructure() const;
    K searchBySerialNumber(int serialNumber);
};


template <class K, class V>
Tree<K, V>::Node::Node(K key, V value) {
    this->key = key;
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
}

template <class K, class V>
Tree<K, V>::Iterator::Iterator(Tree* tree) {
    this->ptr = tree;

    this->current = tree->root;
    if (this->current != nullptr) {
        while (this->current->left != nullptr) {
            this->current = this->current->left;
        }
    }
}

template <class K, class V>
K& Tree<K, V>::Iterator::operator*() {
    if (this->current == nullptr) {
        throw std::invalid_argument("Последний элемент нельзя разыменовывать");
    }
    return this->current->key;
}

template <class K, class V>
typename Tree<K, V>::Node* Tree<K, V>::Iterator::getNextParent(Node* fromNode) {
    Node* pred = this->ptr->root;

    if (pred == fromNode) {
        return nullptr;
    }

    while (pred->left != fromNode && pred->right != fromNode) {
        if (pred->key > fromNode->key) {
            pred = pred->left;
        }
        else {
            pred = pred->right;
        }
    }
    if (pred->key < fromNode->key) {
        return this->getNextParent(pred);
    }
    return pred;
}

template <class K, class V>
typename Tree<K, V>::Iterator& Tree<K, V>::Iterator::operator++() {
    if (this->current == nullptr) {
        throw std::invalid_argument("Вы уже на последнем элементе дерева");
    }

    if (this->current->right != nullptr) {
        this->current = this->current->right;
        while (this->current->left != nullptr) {
            this->current = this->current->left;
        }
    }
    else {
        this->current = this->getNextParent(this->current);
    }
    return *this;
}

template <class K, class V>
bool Tree<K, V>::Iterator::operator==(const Iterator& other) {
    return this->current == other.current;
}

template <class K, class V>
typename Tree<K, V>::Iterator Tree<K, V>::begin() {
    return Iterator(this);
}

template <class K, class V>
typename Tree<K, V>::Iterator Tree<K, V>::end() {
    Iterator temp = Iterator(this);
    for (int i = 0; i < this->getSize(); i++) {
        ++temp;
    }
    return temp;
}

template <class K, class V>
Tree<K, V>::Tree() {
    this->root = nullptr;
}

template <class K, class V>
int Tree<K, V>::countAllSubNodes(Node* node) const {
    int counter = 0;
    if (node == nullptr) {
        return counter;
    }
    counter += this->countAllSubNodes(node->left);
    counter += this->countAllSubNodes(node->right);
    counter++;
    return counter;
}

template <class K, class V>
int Tree<K, V>::getSize() const {
    return this->countAllSubNodes(this->root);
}

template <class K, class V>
void Tree<K, V>::insert(K key, V value) {
    if (this->root == nullptr) {
        this->root = new Node(key, value);
        return;
    }

    Node* node = this->root;
    Node* pred = nullptr;
    while (node != nullptr) {
        pred = node;
        if (key == node->key) {
            node->value = value;
            return;
        }

        if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    if (key < pred->key) {
        pred->left = new Node(key, value);
    }
    else {
        pred->right = new Node(key, value);
    }
}

template <class K, class V>
void Tree<K, V>::removeAllSubNodes(Node*& node) {
    if (node == nullptr) {
        return;
    }
    this->removeAllSubNodes(node->left);
    this->removeAllSubNodes(node->right);
    delete node;
    node = nullptr;
}

template <class K, class V>
void Tree<K, V>::clear() {
    this->removeAllSubNodes(this->root);
}

template <class K, class V>
bool Tree<K, V>::isEmtpy() const {
    return this->root == nullptr;
}

template <class K, class V>
V Tree<K, V>::search(K key) const {
    Node* node = this->root;
    while (node != nullptr && key != node->key) {
        if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    if (node == nullptr) {
        throw std::invalid_argument("В дереве нет узла с переданным ключем");
    }
    return node->value;
}

template <class K, class V>
void Tree<K, V>::remove(K key) {
    Node* node = this->root;
    Node* pred = nullptr;
    while (node != nullptr && node->key != key) {
        pred = node;
        if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    if (node == nullptr) {
        return;
    }

    if (node->left == nullptr || node->right == nullptr) {
        Node* newNode = nullptr;
        if (node->left == nullptr) {
            newNode = node->right;
        }
        else {
            newNode = node->left;
        }

        if (node == pred->left) {
            pred->left = newNode;
        }
        else {
            pred->right = newNode;
        }

        delete node;
    }
    else {
        Node* parent = nullptr;
        Node* temp = node->right;

        while (temp->left != nullptr) {
            parent = temp;
            temp = temp->left;
        }
        if (parent != nullptr) {
            parent->left = temp->right;
        }
        else {
            node->right = temp->right;
        }

        node->key = temp->key;
        delete temp;
    }
}

template <class K, class V>
void Tree<K, V>::printAllKeysByScheme(Node* node) const {
    if (node == nullptr) {
        return;
    }
    this->printAllKeysByScheme(node->left);
    this->printAllKeysByScheme(node->right);
    std::cout << node->key << " ";
}


template <class K, class V>
void Tree<K, V>::printKeysByScheme() const {
    this->printAllKeysByScheme(this->root);
    std::cout << std::endl;
}

template <class K, class V>
void Tree<K, V>::showKeyWithIndent(Node* node, const int level) const {
    if (node == nullptr) {
        return;
    }
    this->showKeyWithIndent(node->right, level + 1);
    for (int i = 0; i < 3 * level; i++) {
        std::cout << " ";
    }
    std::cout << node->key << std::endl;
    this->showKeyWithIndent(node->left, level + 1);
}


template <class K, class V>
void Tree<K, V>::printStructure() const {
    this->showKeyWithIndent(this->root, 0);
    std::cout << std::endl;
}

template <class K, class V>
K Tree<K, V>::searchBySerialNumber(const int serialNumber) {
    Iterator iterator = this->begin();
    for (int i = 0; i < serialNumber; i++) {
        ++iterator;
    }
    return *iterator;
}


#endif //TREE_H
