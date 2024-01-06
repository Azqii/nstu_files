#include <iostream>
#include "Tree.h"

int main() {
    Tree<int, int> tree;
    tree.insert(2, 22);
    tree.insert(1, 11);
    tree.insert(5, 55);
    tree.insert(4, 44);
    tree.insert(3, 33);
    tree.insert(7, 77);
    tree.insert(8, 88);

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

    tree.clear();
    std::cout << tree.getSize() << std::endl;
    return 0;
}
