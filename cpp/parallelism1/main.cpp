#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <fstream>
#include <cmath>
#include <windows.h>

std::vector<int> load_array_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
    }

    std::string dummy;
    std::getline(infile, dummy);  // Пропуск строки с размерностью

    std::vector<int> array;
    int value;
    while (infile >> value) {
        array.push_back(value);
    }

    return array;
}

void save_array_to_file(const std::string& filename, const std::vector<int>& arr) {
    std::ofstream outfile(filename);
    if (!outfile) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }

    for (int val : arr) {
        outfile << val << "\n";
    }
}

void merge(std::vector<int>& array, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            temp[k] = array[i];
            ++k;
            ++i;
        }
        else {
            temp[k] = array[j];
            ++k;
            ++j;
        }
    }

    while (i <= mid) {
        temp[k] = array[i];
        ++k;
        ++i;
    }

    while (j <= right) {
        temp[k] = array[j];
        ++k;
        ++j;
    }

    for (int idx = 0; idx < k; ++idx)
        array[left + idx] = temp[idx];
}

void merge_sort_seq(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort_seq(arr, left, mid);
    merge_sort_seq(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge_sort_par(std::vector<int>& arr, int left, int right, int depth) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    #pragma omp task shared(arr) if(depth > 0)
    merge_sort_par(arr, left, mid, depth - 1);

    #pragma omp task shared(arr) if(depth > 0)
    merge_sort_par(arr, mid + 1, right, depth - 1);

    #pragma omp taskwait
    merge(arr, left, mid, right);
}

int main() {
     SetConsoleOutputCP(65001);
     SetConsoleCP(65001);

    try {
        std::string input_filename;
        std::cout << "Введите имя текстового файла с массивом: ";
        std::getline(std::cin, input_filename);

        std::vector<int> arr = load_array_from_file(input_filename);

        if (arr.empty()) {
            throw std::runtime_error("Файл пуст или содержит недопустимые данные.");
        }

        std::vector<int> arr_seq = arr;
        std::vector<int> arr_par = arr;

        // Последовательная сортировка
        auto start = std::chrono::high_resolution_clock::now();
        merge_sort_seq(arr_seq, 0, arr_seq.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_seq = end - start;
        std::cout << "Время последовательной сортировки: " << duration_seq.count() << " секунд" << std::endl;

        // Параллельная сортировка

        // Определяем оптимальную максимальную глубину для создания новых задач, исходя из того, что на каждом следующем уровне рекурсии кол-во задач удваивается
        int start_depth = static_cast<int>(std::log2(omp_get_max_threads()));
        start = std::chrono::high_resolution_clock::now();
        #pragma omp parallel
        {
            #pragma omp single nowait
            merge_sort_par(arr_par, 0, arr_par.size() - 1,start_depth);
        }
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_par = end - start;
        std::cout << "Время параллельной сортировки: " << duration_par.count() << " секунд" << std::endl << std::endl;

        std::cout << "Отсортированные массивы равны: " << std::boolalpha << (arr_seq == arr_par) << std::endl;

        save_array_to_file("sorted_sequential.txt", arr_seq);
        save_array_to_file("sorted_parallel.txt", arr_par);
        std::cout << "Отсортированные массивы можно посмотреть в файлах sorted_sequential.txt и sorted_parallel.txt" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what();
        return 1;
    }
    return 0;
}
