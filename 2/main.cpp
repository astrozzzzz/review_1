/* Продолжение задания №2 */
#include "king.h"
using namespace std;

/**
 * @breif Основная функция программы для решения задачи о хромом короле.
 * @return Код завершения программы (0 при успехе, 1 при ошибке).
 */
int main() {
    // FIX ME переменная объявлена, но не инициализированна
    // int n;
    int n = 0;
    vector<vector<int>> board;
    vector<vector<int>> dp;
    vector<vector<char>> path;
    if (!ReadInput("input1.txt", n, board)) {
        return 1;
    }
    ComputePath(n, board, dp, path);
    string route = ReconstructRoute(n, path);
    WriteOutput("output1.txt", dp[n - 1][0], route);
    return 0;
}