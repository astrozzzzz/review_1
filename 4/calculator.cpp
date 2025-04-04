/**
* Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения, 
* не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
* Вывести значение целочисленного выражения, заданного в виде строки S.Выражение
* определяется следующим образом :
* <выражение> :: = <цифра> | (<выражение><знак><выражение>)
* < знак > :: = +| − | *
*/

#include "calculator.h"

using namespace std;


/**
 * @brief Преобразует строку в число или вычисляет вложенное выражение.
 * @param s Входная строка, представляющая число или выражение в скобках.
 * @return Целочисленное значение выражения.
 */
// FIX ME функция должна иметь понятное название
// int Num(string s)
int ParseNumber(const string& s) {
    if (s[0] == '(' && s[s.length() - 1] == ')') {
        return Calc(s.substr(1, s.length() - 2));
    }
    else {
        return stoi(s);
    }
}

/**
 * @brief Вычисляет произведение двух подвыражений, разделённых знаком '*'.
 * @param s Входная строка, представляющая выражение.
 * @return Результат умножения.
 */
// FIX ME функция должна иметь понятное название
// int Term(string s)
int ComputeProduct(const string& s) {
    int i = s.length() - 1;
    int level = 0;
    int pos = -1;
    while (i >= 0) {
        if (s[i] == ')') {
            level++;
        }
        else if (s[i] == '(') {
            level--;
        }
        else if (level == 0 && s[i] == '*') {
            pos = i;
            break;
        }
        i--;
    }

    if (pos == -1) {
        return ParseNumber(s);
    }

    return ComputeProduct(s.substr(0, pos)) * ParseNumber(s.substr(pos + 1));
}

/**
 * @brief Рекурсивно вычисляет значение целочисленного выражения.
 * @param s Входная строка, представляющая выражение.
 * @return Результат вычисления.
 */
// FIX ME функция должна объявляться в заголовочном файле
// int Calc(string s);
int Calc(const string& s) {
    int i = s.length() - 1;
    int level = 0;
    int pos = -1;
    while (i >= 0) {
        if (s[i] == ')') {
            level++;
        }
        else if (s[i] == '(') {
            level--;
        }
        else if (level == 0 && (s[i] == '+' || s[i] == '-')) {
            pos = i;
            break;
        }
        i--;
    }

    if (pos == -1) {
        return ComputeProduct(s);
    }

    char op = s[pos];
    if (op == '+') {
        return Calc(s.substr(0, pos)) + ComputeProduct(s.substr(pos + 1));
    }
    else if (op == '-') {
        return Calc(s.substr(0, pos)) - ComputeProduct(s.substr(pos + 1));
    }

    return 0;
}