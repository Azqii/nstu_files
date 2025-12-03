//
// Created by Dima on 01.12.2025.
//
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <cmath>
#include <windows.h>  // comment on Linux
#include "Hashtable.h"

#pragma execution_character_set("utf-8")


std::string randomKey(size_t len = 10) {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    std::string s;
    s.reserve(len);
    for (size_t i = 0; i < len; ++i)
        s.push_back(alphabet[rand() % 26]);
    return s;
}


double computeChi2(const std::vector<size_t>& freq, size_t P, size_t m)
{
    double expected = double(P) / m;
    double chi2 = 0.0;

    for (size_t i = 0; i < m; ++i) {
        double diff = freq[i] - expected;
        chi2 += diff * diff;
    }

    return (m / double(P)) * chi2;
}


double runOneExperiment(size_t m, bool printRange) {
    Hashtable<int> table(m);

    size_t actual_m = table.getCapacity();
    size_t P = actual_m * 20;

    if (printRange) {
        std::cout << "Диапазон допустимых значений: " << actual_m - sqrt(actual_m) <<
        " <= X^2 <= " << actual_m + sqrt(actual_m) << std::endl;
    }

    for (size_t i = 0; i < P; ++i)
        table.insert(randomKey(), 0);

    std::vector<size_t> freq(actual_m);
    for (size_t i = 0; i < actual_m; ++i)
        freq[i] = table.getBucketSize(i);

    double result = computeChi2(freq, P, actual_m);
    std::cout << "X^2 для отдельного эксперимента: " << result << std::endl;

    return result;
}


double runChi2Series(size_t m, int experiments) {
    double sum = 0;
    for (int i = 0; i < experiments; ++i) {
        sum += runOneExperiment(m, i == 0);
    }

    return sum / experiments;
}


int main() {
    SetConsoleOutputCP(65001);  // Comment on linux
    SetConsoleCP(65001);  // Comment on linux

    size_t m = 101;
    int experiments = 20;

    std::srand(std::time(nullptr));

    double chi2 = runChi2Series(m, experiments);
    std::cout << "Среднее X^2 на основе 20 экспериментов = " << chi2 << std::endl;

    return 0;
}
