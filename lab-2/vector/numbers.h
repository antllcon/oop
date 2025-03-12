#ifndef NUMBERS_H
#define NUMBERS_H

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

/**
 * @brief Читает числа из стандартного ввода и сохраняет их в вектор.
 * @param numbers Вектор, в который будут сохранены числа.
 * @throws std::runtime_error Если ввод содержит нечисловые данные.
 */
void ReadNumbers(std::vector<double>& numbers);

/**
 * @brief Обрабатывает вектор чисел: находит сумму минимальных элементов и добавляет её к каждому
 * элементу.
 * @param numbers Вектор чисел для обработки.
 */
void ProcessNumbers(std::vector<double>& numbers);

/**
 * @brief Выводит отсортированный вектор чисел с заданной точностью.
 * @param numbers Вектор чисел для вывода.
 */
void PrintSortedNumbers(const std::vector<double>& numbers);

#endif