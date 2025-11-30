//
// Created by Dima on 01.12.2025.
//
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
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


double runOneExperiment(size_t m, size_t P) {
    Hashtable<int> table(m);

    for (size_t i = 0; i < P; ++i)
        table.insert(randomKey(), 0);

    std::vector<size_t> freq(m);
    for (size_t i = 0; i < m; ++i)
        freq[i] = table.getBucketSize(i);

    return computeChi2(freq, P, m);
}


double runChi2Series(size_t m, size_t P, int experiments) {
    double sum = 0;
    for (int i = 0; i < experiments; ++i) {
        sum += runOneExperiment(m, P);
    }

    return sum / experiments;
}


int main() {
    SetConsoleOutputCP(65001);  // Comment on linux
    SetConsoleCP(65001);  // Comment on linux

    size_t m = 101;
    size_t P = 10100;
    int experiments = 20;

    std::srand(std::time(nullptr));

    double chi2 = runChi2Series(m, P, experiments);
    std::cout << "Среднее Хи^2 на основе 20 экспериментов = " << chi2 << std::endl;

    return 0;
}
