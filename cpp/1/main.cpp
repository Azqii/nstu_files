#include <iostream>

// Рекурсивная функция поиска минимального числа
int min(int amount) {
    int number;
    // Объявление переменной для вводимого числа
    std::cin >> number; // Ввод числа.
    if (amount == 1)
        return number;
    // Возвращаем последнее (или единственное) число.
    int number_2 = min(amount - 1); // Вызов рекурсии.
    // Сравниваем введенное и полученное в ходе выполнения рекурсии числа.
    // Возвращаем наименьшее.
    if (number_2 < number)
        return number_2;
    return number;
}

int main() {
    int k, min_number; // Объявление переменных для кол-ва чисел и минимального из них.
    std::cout << "Enter the amount of numbers: ";
    std::cin >> k; // Ввод кол-ва чисел
    std::cout << "Enter the numbers: ";
    min_number = min(k);
    std::cout << "Min. number is " << min_number;
    return 0;
}