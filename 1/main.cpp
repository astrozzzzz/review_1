/*
 * Продолжение задания №1
 */
#include "artifact_solver.h"

using namespace std;


/**
 * @breif Точка входа программы, организующая процесс выбора артефактов.
 * @return возвращает 0
*/
int main() {
    ifstream stream;
    stream.open("a.txt");
    // FIX ME ненужные переменные
    //int n, b, k, weight, volume, ind_i, ind_j;
    int n = 0;
    int b = 0;
    vector<int> weight_vector(n + 1);
    vector<int> volume_vector(n + 1);
    // FIX ME отсутствовала проверка на корректное открытие файла
    if (!ReadInput(stream, n, b, weight_vector, volume_vector)) {
        cout << "Не получилось открыть файл." << endl;
        return 1;
    }
    // FIX ME не было закрытия файла
    stream.close();
    // FIX ME Отсутствовала проверка входных данных
    if (!ValidateInput(n, b, weight_vector, volume_vector)) {
        cout << "Некорректные входные данные." << endl;
        return 1;
    }

    vector<vector<int>> main_vector(n + 1, vector<int>(b + 1, 0));
    vector<vector<int>> count(n + 1, vector<int>(b + 1, 0));
    vector<vector<int>> volume_main(n + 1, vector<int>(b + 1, 0));

    FillDPTables(n, b, weight_vector, volume_vector, main_vector, count, volume_main);

    int best_weight = 0;
    int best_count = 0;
    int best_volume = 0;
    int best_j = 0;

    FindBestSolution(n, b, main_vector, count, volume_main, best_weight, best_count, best_volume, best_j);

    OutputResults(best_weight, best_volume, n, best_j, main_vector, weight_vector);

    return 0;
}