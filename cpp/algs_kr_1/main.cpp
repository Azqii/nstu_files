#include <iostream>
#include <windows.h>
#include "Tree.h"
#pragma execution_character_set("utf-8")

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Tree<int, int> tree;
    tree.insert(2, 22);
    tree.insert(1, 11);
    tree.insert(5, 55);
    tree.insert(4, 44);
    tree.insert(3, 33);
    tree.insert(7, 77);
    tree.insert(8, 88);
    tree.insert(9, 99);

    std::cout << "structure:" << std::endl;
    tree.printStructure();

    std::cout << tree.getSize() << std::endl;

    std::cout << "Value of the node with the key 3: " << tree.search(3) << std::endl;

    std::cout << "Keys with 7: ";
    tree.printKeysByScheme();

    tree.remove(7);
    std::cout << "Keys without 7: ";
    tree.printKeysByScheme();
    std::cout << tree.getSize() << std::endl;

    std::cout << "structure:" << std::endl;
    tree.printStructure();

    std::cout << "iterate begin/end:" << std::endl;
    auto elem = tree.begin();
    auto lastElem = tree.end();
    std::cout << "after end" << std::endl;
    while (true) {
        if (elem == lastElem) {
            std::cout << "the end" << std::endl;
            break;
        }
        std::cout << *elem << " ";
        ++elem;
    }

    std::cout << "new iterate:" << std::endl;
    auto elem_1 = tree.begin();
    for (int i = 0; i < tree.getSize(); i++) {
        std::cout << *elem_1 << " ";
        ++elem_1;
    }
    std::cout << std::endl << std::endl;

    std::cout << "Key at 5 (position): " << tree.searchBySerialNumber(5) << std::endl << std::endl;

    tree.clear();
    std::cout << tree.getSize() << std::endl << std::endl;
    return 0;
}
