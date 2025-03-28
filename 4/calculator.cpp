/*
* Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения, 
* не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
* Вывести значение целочисленного выражения, заданного в виде строки S.Выражение
* определяется следующим образом :
* <выражение> :: = <цифра> | (<выражение><знак><выражение>)
* < знак > :: = +| − | *
*/

// FIX ME: фигурные скобки должны быть на новой строке в строках 17, 21, 23, 27, 38, 42, 44, 47, 54, 58, 60, 63, 65, 67, 76, 80

#include "calculator.h"

using namespace std;

// @breif Объявление функции для вычисления выражения
// FIX ME функция должна быть в snake case
// int Calc(string s);
int calc(const string& s);

/*
 * @brief Преобразует строку в число или вычисляет вложенное выражение.
 * @param s Входная строка, представляющая число или выражение в скобках.
 * @return Целочисленное значение выражения.
 */
 // FIX ME функция должна быть в snake case и иметь понятное название
// int Num(string s)
int parse_number(const string& s)
{
	if (s[0] == '(' && s[s.length() - 1] == ')')
	{
		return calc(s.substr(1, s.length() - 2));
	}
	else
	{
		return stoi(s);
	}
}

/*
 * @brief Вычисляет произведение двух подвыражений, разделённых знаком '*'.
 * @param s Входная строка, представляющая выражение.
 * @return Результат умножения.
 */
 // FIX ME функция должна быть в snake case и иметь понятное название
// int Term(string s)
int compute_product(const string& s)
{
	int i = s.length() - 1;
	int level = 0;
	int pos = -1;
	while (i >= 0)
	{
		if (s[i] == ')')
		{
			level++;
		}
		else if (s[i] == '(')
		{
			level--;
		}
		else if (level == 0 && s[i] == '*')
		{
			pos = i;
			break;
		}
		i--;
	}

	if (pos == -1)
	{
		return parse_number(s);
	}

	return compute_product(s.substr(0, pos)) * parse_number(s.substr(pos + 1));
}

/*
 * @brief Рекурсивно вычисляет значение целочисленного выражения.
 * @param s Входная строка, представляющая выражение.
 * @return Результат вычисления.
 */
int calc(const string& s)
{
	int i = s.length() - 1;
	int level = 0;
	int pos = -1;
	while (i >= 0)
	{
		if (s[i] == ')')
		{
			level++;
		}
		else if (s[i] == '(')
		{
			level--;
		}
		else if (level == 0 && (s[i] == '+' || s[i] == '-'))
		{
			pos = i;
			break;
		}
		i--;
	}

	if (pos == -1)
	{
		return compute_product(s);
	}

	char op = s[pos];
	if (op == '+')
	{
		return calc(s.substr(0, pos)) + compute_product(s.substr(pos + 1));
	}
	else if (op == '-')
	{
		return calc(s.substr(0, pos)) - compute_product(s.substr(pos + 1));
	}

	return 0;
}

/*
 * @brief Основная функция программы для вычисления целочисленного выражения.
 * Считывает строку с выражением и выводит его значение.
 * @return Код завершения программы (0 при успехе).
 */
int main()
{
	setlocale(0, "");
	string s;
	cout << "Введите строку вида - <цифра> | (<выражение><знак><выражение>), где знак - (+ | - | *):" << endl;
	cin >> s;
	cout << "Результат: " << calc(s) << endl;

	return 0;
}