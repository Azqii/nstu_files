#include <iostream>
#include <string>

// Проверка баланса скобок
int bracket_balance(std::string line, char bracket_type = '!', int j = 0) {
    // Нахождение обратной скобки для выхода.
    char right_bracket;
    if (bracket_type == '(')
        right_bracket = ')';
    else if (bracket_type == '[')
        right_bracket = ']';
    else if (bracket_type == '{')
        right_bracket = '}';
    // Итерирование по строке
    for (j; j < line.length(); j++) {
        // Возвращаем место нахождения обратной скобки
        if (line[j] == right_bracket)
            return j;
        // Вызываем рекурсию при нахождении левой скобки
        // Присваиваем индексу значение найденной обратной скобки
        if (line[j] == '(' || line[j] == '[' || line[j] == '{')
            j = bracket_balance(line, line[j], j + 1);
        // Выход из рекурсии, если не нашлось обратной скобки
        if (j == -1)
            return -1;
    }
    // Возвращаем 1, если вход в функцию был не со скобки
    // -1, если со скобки и обратная ей в цикле не нашлась
    if (bracket_type == '!')
        return 1;
    return -1;
}

int main() {
    // Объявление переменной для вводимого текста
    std::string text;
    std::cout << "Enter the text to check bracket balance:" <<
              std::endl;
    // Ввод текста для проверки баланса скобок
    std::getline(std::cin, text);
    // Вывод, в зависимости от вернувшегося значения
    if (bracket_balance(text) == -1)
        std::cout << "\nBrackets are NOT balanced";
    else
        std::cout << "\nBrackets are balanced";
    return 0;
}