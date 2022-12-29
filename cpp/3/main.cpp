#include <iostream>

struct btree {
    int value;
    struct btree *left, *right;
};

// Включение вершины в дерево
void Ins_Btree(int val, btree **q) {
    if (*q == NULL) // Нашли место для добавления
    {
        *q = new btree;
        (*q)->left = (*q)->right = NULL;
        (*q)->value = val;
        return;
    }
    if ((*q)->value > val)
        Ins_Btree(val, &(*q)->left); // Добавляем в левое поддерево
    else
        Ins_Btree(val, &(*q)->right); // Добавляем в правое поддерево
}

// Вывод содержимого дерева
void Print_Btree(btree *p) {
    if (p == NULL)
        return;
    Print_Btree(p->left);
    std::cout << p->value << " ";
    Print_Btree(p->right);
}

// Создание копии дерева
btree *copy_btree(btree *T1, btree *T2) {
    if (T1 == NULL) // Условие выхода из рекурсии при отсутствующем элементе
        return T1;
    // Добавление значения элемента дерева T1 в T2
    Ins_Btree(T1->value, &T2);
    // Вызов рекурсии для левого поддерева T1
    copy_btree(T1->left, T2);
    // Вызов рекурсии для правого поддерева T1
    copy_btree(T1->right, T2);
    return T2;
}

int main() {
    int d; // Инициализация вспомогательной переменной для заполнения дерева
    btree *root = NULL, *new_root = NULL; // Инициализация переменных для 2-ух деревьев
    std::cout << "Enter the numbers for the original btree (0 to stop):\n";
    while (true) // Цикл для заполнения 1-го дерева
    {
        std::cin >> d;
        if (d == 0)
            break;
        Ins_Btree(d, &root);
    }
    // Вывод оригинального дерева
    std::cout << "Original btree:\n";
    Print_Btree(root);
    // Вывод скопированного дерева, полученного вызовом функции
    std::cout << "\nCopied btree:\n";
    Print_Btree(copy_btree(root, new_root));
    return 0;
}