//Хромой король.На квадратной доске в каждой клетке короля ожидают неприятности в количестве 
//от 0 до 30. Хромой король, находящийся в правом верхнем углу, мечтает попасть в левый нижний 
//угол.При этом он может передвигаться только в клетку слева или снизу и хочет, чтобы сумма 
//всех неприятностей, оказавшихся у него на пути, была бы минимальной.
//Определить эту сумму и путь, каким образом должен двигаться король.Ввод и вывод организовать 
//при помощи текстовых файлов.Формат входных данных : в первой строке входного файла
//записано число N - размер доски(1 < N < 80).Далее следует N строк, каждая из которых содержит
//N чисел - количество неприятностей в клетках доски.В первую строку выходного файл нужно
//вывести единственное число : минимальную сумму, а во второй строке вывести путь в виде
//строки символов, обозначив символом L движение влево, а символом D - движение вниз.	


// FIX ME: фигурные скобки должны быть на новой строке в строках 22, 25, 31, 41, 43, 54, 60, 66, 68, 70, 74, 80, 82, 85
// FIX ME: комментарии переписаны для объяснения назначения, а не механики, в строках 40, 50, 51, 55, 61, 67, 79, 88, 94

#include "king.h"

using namespace std;

/**
 * Основная функция программы для решения задачи о хромом короле.
 * Считывает данные из файла, вычисляет минимальную сумму неприятностей
 * и путь от правого верхнего угла к левого нижнему, затем записывает результат.
 * @return Код завершения программы (0 при успехе, 1 при ошибке).
 */
int main()
{
	ifstream input_file("input1.txt");
	ofstream output_file("output1.txt");

	if (!input_file.is_open())
	{
		cerr << "Не удалось открыть входной файл!" << endl;
		return 1;
	}

	if (!output_file.is_open())
	{
		cerr << "Не удалось открыть выходной файл!" << endl;
		input_file.close();
		return 1;
	}

	int n;
	input_file >> n;

	// Матрица для хранения значений доски с неприятностями
	vector<vector<int>> board(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			input_file >> board[i][j];
		}
	}

	input_file.close();

	// Матрица для хранения минимальных сумм неприятностей
	vector<vector<int>> dp(n, vector<int>(n, 0));
	// Матрица для восстановления пути ('L' - влево, 'D' - вниз)
	vector<vector<char>> path(n, vector<char>(n, ' '));

	// Устанавливаем начальную точку в правом верхнем углу
	dp[0][n - 1] = board[0][n - 1];

	// Заполняем первый столбец движением только вниз
	for (int i = 1; i < n; ++i)
	{
		dp[i][n - 1] = dp[i - 1][n - 1] + board[i][n - 1];
		path[i][n - 1] = 'D';
	}

	// Заполняем первую строку движением только влево
	for (int j = n - 2; j >= 0; --j)
	{
		dp[0][j] = dp[0][j + 1] + board[0][j];
		path[0][j] = 'L';
	}

	// Заполняем остальную матрицу, выбирая минимальный путь
	for (int i = 1; i < n; ++i)
	{
		for (int j = n - 2; j >= 0; --j)
		{
			if (dp[i - 1][j] < dp[i][j + 1])
			{
				dp[i][j] = dp[i - 1][j] + board[i][j];
				path[i][j] = 'D';
			}
			else
			{
				dp[i][j] = dp[i][j + 1] + board[i][j];
				path[i][j] = 'L';
			}
		}
	}

	// Восстанавливаем маршрут от левого нижнего угла к правому верхнему
	string route = "";
	int row = n - 1;
	int col = 0;

	while (row != 0 || col != n - 1)
	{
		route += path[row][col];
		if (path[row][col] == 'D')
		{
			row--;
		}
		else
		{
			col++;
		}
	}

	// Переворачиваем маршрут для вывода от старта к финишу
	reverse(route.begin(), route.end());

	// Записываем результат в выходной файл
	output_file << dp[n - 1][0] << endl;
	output_file << route << endl;

	output_file.close();

	return 0;
}