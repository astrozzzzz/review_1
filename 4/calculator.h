#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>

/**
 * @brief Рекурсивно вычисляет значение целочисленного выражения.
 * @param s Входная строка, представляющая выражение.
 * @return Результат вычисления.
 */
int Calc(const std::string& s);

/**
 * @brief Преобразует строку в число или вычисляет вложенное выражение.
 * @param s Входная строка, представляющая число или выражение в скобках.
 * @return Целочисленное значение выражения.
 */
int ParseNumber(const std::string& s);

/**
 * @brief Вычисляет произведение двух подвыражений, разделённых знаком '*'.
 * @param s Входная строка, представляющая выражение.
 * @return Результат умножения.
 */
int ComputeProduct(const std::string& s);

#endif