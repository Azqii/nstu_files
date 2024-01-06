//
// Created by DimaWin on 05.01.2024.
//

#ifndef TREE_H
#define TREE_H


template <class K, class V>
class Tree
{
protected:
    class Node
    {
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
    class Iterator
    {
    private:
        Tree* ptr;
        Node* cur;

    public:
        Iterator(Tree *);  // TODO
        K& operator *();  // TODO
        Iterator &operator ++();  // TODO
        bool operator ==(const Iterator&);  // TODO
    };

    Iterator begin();  // TODO
    Iterator end();  // TODO

    Tree();
    int getSize() const;
    void clear();
    bool isEmtpy() const;
    V search(K key) const;
    void insert(K key, V value);
    void remove(K key);
    void printKeysByScheme() const;
    void printStructure() const;
    K searchBySerialNumber(int serialNumber) const;  // TODO
};


template <class K, class V>
Tree<K, V>::Node::Node(K key, V value)
{
    this->key = key;
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
}

template <class K, class V>
Tree<K, V>::Tree()
{
    this->root = nullptr;
}

template <class K, class V>
int Tree<K, V>::countAllSubNodes(Node* node) const
{
    int counter = 0;
    if (node == nullptr)
    {
        return counter;
    }
    counter += this->countAllSubNodes(node->left);
    counter += this->countAllSubNodes(node->right);
    counter++;
    return counter;
}

template <class K, class V>
int Tree<K, V>::getSize() const
{
    return this->countAllSubNodes(this->root);
}

template <class K, class V>
void Tree<K, V>::insert(K key, V value)
{
    if (this->root == nullptr)
    {
        this->root = new Node(key, value);
        return;
    }

    Node* node = this->root;
    Node* pred = nullptr;
    while (node != nullptr)
    {
        pred = node;
        if (key == node->key)
        {
            node->value = value;
            return;
        }

        if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    if (key < pred->key)
    {
        pred->left = new Node(key, value);
    }
    else
    {
        pred->right = new Node(key, value);
    }
}

template <class K, class V>
void Tree<K, V>::removeAllSubNodes(Node*& node)
{
    if (node == nullptr)
    {
        return;
    }
    this->removeAllSubNodes(node->left);
    this->removeAllSubNodes(node->right);
    delete node;
    node = nullptr;
}

template <class K, class V>
void Tree<K, V>::clear()
{
    this->removeAllSubNodes(this->root);
}

template <class K, class V>
bool Tree<K, V>::isEmtpy() const
{
    return this->root == nullptr;
}

template <class K, class V>
V Tree<K, V>::search(K key) const
{
    Node* node = this->root;
    while (node != nullptr && key != node->key)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    if (node == nullptr)
    {
        throw std::invalid_argument("There's no such node with the given key");
    }
    return node->value;
}

template <class K, class V>
void Tree<K, V>::remove(K key)
{
    Node* node = this->root;
    Node* pred = nullptr;
    while (node != nullptr && node->key != key)
    {
        pred = node;
        if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    if (node == nullptr)
    {
        return;
    }

    if (node->left == nullptr || node->right == nullptr)
    {
        Node* newNode = nullptr;
        if (node->left == nullptr)
        {
            newNode = node->right;
        }
        else
        {
            newNode = node->left;
        }

        if (node == pred->left)
        {
            pred->left = newNode;
        }
        else
        {
            pred->right = newNode;
        }

        delete node;
    }
    else
    {
        Node* parent = nullptr;
        Node* temp = node->right;

        while (temp->left != nullptr)
        {
            parent = temp;
            temp = temp->left;
        }
        if (parent != nullptr)
        {
            parent->left = temp->right;
        }
        else
        {
            node->right = temp->right;
        }

        node->key = temp->key;
        delete temp;
    }
}

template <class K, class V>
void Tree<K, V>::printAllKeysByScheme(Node* node) const
{
    if (node == nullptr)
    {
        return;
    }
    this->printAllKeysByScheme(node->left);
    this->printAllKeysByScheme(node->right);
    std::cout << node->key << " ";
}


template <class K, class V>
void Tree<K, V>::printKeysByScheme() const
{
    this->printAllKeysByScheme(this->root);
    std::cout << std::endl;
}

template <class K, class V>
void Tree<K, V>::showKeyWithIndent(Node* node, int level) const
{
    if (node == nullptr)
    {
        return;
    }
    this->showKeyWithIndent(node->right, level + 1);
    for (int i = 0; i < 3 * level; i++)
    {
        std::cout << " ";
    }
    std::cout << node->key << std::endl;
    this->showKeyWithIndent(node->left, level + 1);
}


template <class K, class V>
void Tree<K, V>::printStructure() const
{
    this->showKeyWithIndent(this->root, 0);
    std::cout << std::endl;
}


#endif //TREE_H
