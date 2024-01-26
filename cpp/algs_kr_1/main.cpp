#include <iostream>
// #include <windows.h> // Comment on linux
#include "Tree.h"

#pragma execution_character_set("utf-8")

using std::cout, std::cin, std::endl;

int main() {
    // SetConsoleOutputCP(65001);  // Comment on linux
    // SetConsoleCP(65001);  // Comment on linux

    Tree<int, int> tree;
    Tree<int, int>::Iterator it = tree.begin();

    int x;
    while (true) {
        cout << endl << "Выбор действия:" << endl << endl;
        cout << "1. Вставить пару в дерево" << endl;
        cout << "2. Удалить пару из дерева по ключу" << endl;
        cout << "3. Посчитать размер дерева" << endl;
        cout << "4. Очистить дерево" << endl;
        cout << "5. Проверить дерево на пустоту" << endl;
        cout << "6. Обойти дерево (Lt -> Rt -> t)" << endl;
        cout << "7. Дополнительная операция: поиск k –го по порядку ключа в деревепоиск k –го по порядку ключа в дереве" << endl;
        cout << "8. Напечатать дерево" << endl;
        cout << "9. Поиск элемента по ключу" << endl;
        cout << "10. Обнулить итератор (.begin())" << endl;
        cout << "11. Показать содержание итератора (*it)" << endl;
        cout << "12. Перевести итератор на следующий элемент (++it)" << endl;
        cout << "13. Присвоить итератору новое значение (cin >> *it)" << endl;

        cout << endl;
        cin >> x;
        cout << endl;

        try {
            switch (x) {
                case 1: {
                    int key, value;

                    cin >> key >> value;
                    tree.insert(key, value);
                    break;
                }
                case 2: {
                    int key;

                    cin >> key;
                    tree.remove(key);
                    break;
                }
                case 3: {
                    cout << tree.getSize() << endl;
                    break;
                }
                case 4: {
                    tree.clear();
                    break;
                }
                case 5: {
                    cout << tree.isEmtpy() << endl;
                    break;
                }
                case 6: {
                    cout << endl;

                    tree.printKeysByScheme();
                    break;
                }
                case 7: {
                    int serialNumber;

                    cin >> serialNumber;

                    cout << endl << tree.searchBySerialNumber(serialNumber) << endl;
                    break;
                }
                case 8: {
                    cout << endl;

                    tree.printStructure();
                    break;
                }
                case 9: {
                    int key;

                    cin >> key;
                    cout << tree.search(key) << endl;
                    break;
                }
                case 10: {
                    it = tree.begin();
                    break;
                }
                case 11: {
                    cout << *it << endl;
                    break;
                }
                case 12: {
                    ++it;
                    break;
                }
                case 13: {
                    cin >> *it;
                    break;
                }
                default: {
                    cout << "Такой команды не существует" << endl;
                    break;
                }
            }
        }
        catch(...) {
            std::cout << "Исключение" << std::endl;
        }
    }
    return 0;
}
