/**
 * Хромой король.На квадратной доске в каждой клетке короля ожидают неприятности в количестве
 * от 0 до 30. Хромой король, находящийся в правом верхнем углу, мечтает попасть в левый нижний
 * угол.При этом он может передвигаться только в клетку слева или снизу и хочет, чтобы сумма
 * всех неприятностей, оказавшихся у него на пути, была бы минимальной.
 * Определить эту сумму и путь, каким образом должен двигаться король.Ввод и вывод организовать
 * при помощи текстовых файлов.Формат входных данных : в первой строке входного файла
 * записано число N - размер доски(1 < N < 80).Далее следует N строк, каждая из которых содержит
 * N чисел - количество неприятностей в клетках доски.В первую строку выходного файл нужно
 * вывести единственное число : минимальную сумму, а во второй строке вывести путь в виде
 * строки символов, обозначив символом L движение влево, а символом D - движение вниз.
*/

// FIX ME: комментарии переписаны для объяснения назначения, а не механики

#include "king.h"

using namespace std;

/**
* @brief Считывает входные данные из файла.
* @param input_filename Имя файла для чтения.
* @param n Ссылка на целое число, в которое будет сохранён размер доски.
* @param board Ссылка на двумерный вектор, в который будет сохранена доска.
* @returns True, если файл был успешно открыт и прочитан, false в противном случае.
*/
bool ReadInput(const string& input_filename, int& n, vector<vector<int>>& board) {
    ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        cerr << "Не удалось открыть входной файл!" << endl;
        return false;
    }
    // FIX ME отсутствовала проверка на корректность входных данных
    if (!(input_file >> n)) {
        cout << "Ошибка: не удалось прочитать размер доски N." << endl;
        input_file.close();
        return false;
    }

    // Инициализация доски
    board.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(input_file >> board[i][j])) {
                cout << "Ошибка: не удалось прочитать значение доски в позиции (" << i << ", " << j << ")." << endl;
                input_file.close();
                return false;
            }
        }
    }
    input_file.close();
    return true;
}

/**
 * @brief Вычисляет минимальную сумму неприятностей и матрицу пути для задачи.
 * @param n Размер доски (N x N).
 * @param board Двумерный вектор, представляющий доску с неприятностями.
 * @param dp Ссылка на двумерный вектор для хранения минимальных сумм.
 * @param path Ссылка на двумерный вектор для хранения направлений пути ('L' — влево, 'D' — вниз).
 */
void ComputePath(int n, const vector<vector<int>>& board,
                 vector<vector<int>>& dp, vector<vector<char>>& path) {
    dp.resize(n, vector<int>(n, 0));
    path.resize(n, vector<char>(n, ' '));
    dp[0][n - 1] = board[0][n - 1];

    for (int i = 1; i < n; ++i) {
        dp[i][n - 1] = dp[i - 1][n - 1] + board[i][n - 1];
        path[i][n - 1] = 'D';
    }

    for (int j = n - 2; j >= 0; --j) {
        dp[0][j] = dp[0][j + 1] + board[0][j];
        path[0][j] = 'L';
    }
    for (int i = 1; i < n; ++i) {
        for (int j = n - 2; j >= 0; --j) {
            if (dp[i - 1][j] < dp[i][j + 1]) {
                // Заполнение первого столбца
                dp[i][j] = dp[i - 1][j] + board[i][j];
                path[i][j] = 'D';
            } else {
                // Заполнение первой строки
                dp[i][j] = dp[i][j + 1] + board[i][j];
                path[i][j] = 'L';
            }
        }
    }
}

/**
 * @brief Восстанавливает маршрут короля от старта к финишу.
 * @param n Размер доски (N x N).
 * @param path Двумерный вектор с направлениями пути.
 * @returns Строка, представляющая последовательность ходов от старта к финишу.
 */
string ReconstructRoute(int n, const vector<vector<char>>& path) {
    string route = "";
    int row = n - 1;
    int col = 0;

    while (row != 0 || col != n - 1) {
        route += path[row][col];
        if (path[row][col] == 'D') {
            row--;
        } else {
            col++;
        }
    }

    // Переворачиваем маршрут для вывода от правого верхнего угла к левому нижнему
    reverse(route.begin(), route.end());
    return route;
}

/**
 * @brief Записывает результат задачи "Хромой король" в выходной файл.
 * @param output_filename Имя файла для записи.
 * @param min_sum Минимальная сумма неприятностей.
 * @param route Строка, представляющая маршрут короля.
 */
void WriteOutput(const string& output_filename, int min_sum, const string& route) {
    ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        cout << "Не удалось открыть выходной файл!" << endl;
        return;
    }

    output_file << min_sum << endl;
    output_file << route << endl;
    output_file.close();
}

