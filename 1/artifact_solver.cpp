/**
 * Археолог нашел N артефактов.Известны веса(сi) и объемы(di) артефактов.Нужно выбрать такое подмножество
 * найденных вещей, чтобы суммарный их вес не превысил B кг, но был наиболее близок к B, а количество
 * взятых артефактов было как можно больше.Известно, что решение единственно.Укажите порядковые номера
 * вещей, которые надо взять.Исходные данные находятся в текстовом файле, в первой строке указаны N и B,
 * а во второй строке значения весов(в кг), в третьей объемы находок(в куб.см).Вывести так же суммарный
 * вес и суммарный объем результата.
*/

#include "artifact_solver.h"
using namespace std;


/**
 * @breif Считывает входные данные
 * @param stream Входной файловый поток для чтения.
 * @param n Ссылка для хранения количества артефактов (N).
 * @param b Ссылка для хранения максимальной грузоподъёмности (B).
 * @param weights Ссылка на вектор для хранения весов артефактов (индексация с 1).
 * @param volumes Ссылка на вектор для хранения объёмов артефактов (индексация с 1).
 * @returns True, если чтение успешно, false в противном случае (например, файл не открыт).
 */
bool ReadInput(ifstream& stream, int& n, int& b, vector<int>& weights, vector<int>& volumes) {
    if (!stream.is_open()) return false;
    // FIX ME Не было проверки на тип входных данных
    if (!(stream >> n)) {
        cout << "Ошибка: не удалось прочитать n как целое число." << endl;
        stream.close();
        return false;
    }
    if (!(stream >> b)) {
        cout << "Ошибка: не удалось прочитать b как целое число." << endl;
        stream.close();
        return false;
    }
    weights.resize(n + 1);
    volumes.resize(n + 1);
    for (int i = 1; i <= n; i++)
        stream >> weights[i];
    for (int i = 1; i <= n; i++)
        stream >> volumes[i];
    return true;
}

/**
 * Проверяет корректность входных данных
 * @param n Количество артефактов.
 * @param b Максимальная грузоподъёмность.
 * @param weights Вектор весов артефактов (индексация с 1).
 * @param volumes Вектор объёмов артефактов (индексация с 1).
 * @returns True, если входные данные валидны, false в противном случае.
 */
bool ValidateInput(int n, int b, const vector<int>& weights, const vector<int>& volumes) {
    if (n <= 0 || b <= 0) return false;
    for (int w : weights) if (w < 0) return false;
    for (int v : volumes) if (v < 0) return false;
    return true;
}

/**
 * @breif Заполняет таблицы динамического программирования
 * @param n Количество артефактов.
 * @param b Максимальная грузоподъёмность.
 * @param weights Вектор весов артефактов (индексация с 1).
 * @param volumes Вектор объёмов артефактов (индексация с 1).
 * @param main_vector Ссылка на 2D-вектор, хранящий максимальные веса для подзадач.
 * @param count Ссылка на 2D-вектор, хранящий количество артефактов для подзадач.
 * @param volume_main Ссылка на 2D-вектор, хранящий общие объёмы для подзадач.
 */
void FillDPTables(int n, int b, const vector<int>& weights, const vector<int>& volumes,
                  vector<vector<int>>& main_vector, vector<vector<int>>& count,
                  vector<vector<int>>& volume_main) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= b; j++) {
            // FIX ME логика заполнения некорректная так как может привышать j
            /*
            if (j >= weight_vector[i])

            {
                main_vector[i][j] = main_vector[i - 1][j] + weight_vector[i];
                sum_volume_vector[i][j] = sum_volume_vector[i - 1][j] + volume_vector[i];
            }
            else
            {
                main_vector[i][j] = main_vector[i - 1][j];
                sum_volume_vector[i][j] = sum_volume_vector[i - 1][j];
            } */
            int without_weight = main_vector[i - 1][j];
            int with_weight = (j >= weights[i]) ? main_vector[i - 1][j - weights[i]] + weights[i] : 0;

            if (with_weight > without_weight) {
                main_vector[i][j] = with_weight;
                count[i][j] = count[i - 1][j - weights[i]] + 1;
                volume_main[i][j] = volume_main[i - 1][j - weights[i]] + volumes[i];
            }
            else {
                main_vector[i][j] = without_weight;
                count[i][j] = count[i - 1][j];
                volume_main[i][j] = volume_main[i - 1][j];
            }
        }
    }
}

/**
 * Находит лучшее решение на основе максимального веса и количества артефактов.
 * @param n Количество артефактов.
 * @param b Максимальная грузоподъёмность.
 * @param main_vector 2D-вектор, хранящий максимальные веса для подзадач.
 * @param count 2D-вектор, хранящий количество артефактов для подзадач.
 * @param volume_main 2D-вектор, хранящий общие объёмы для подзадач.
 * @param best_weight Ссылка для хранения лучшего общего веса, найденного.
 * @param best_count Ссылка для хранения лучшего количества артефактов, найденного.
 * @param best_volume Ссылка для хранения лучшего общего объёма, найденного.
 * @param best_j Ссылка для хранения лучшей использованной грузоподъёмности.
 */
void FindBestSolution(int n, int b, const vector<vector<int>>& main_vector,
                      const vector<vector<int>>& count,
                      const vector<vector<int>>& volume_main,
                      int& best_weight, int& best_count, int& best_volume, int& best_j) {
    // FIX ME неоптимальный поиск лучшего решения (перебор это плохо)
    /*k = b;
    bool flag = true;
    while (flag == true && k >= 1)
    {
        for (int i = n; i >= 1; i--)
        {
            for (int j = b; j >= 1; j--)
            {
                if (main_vector[i][j] == k)
                {
                    ind_i = i; ind_j = j;
                    weight = main_vector[i][j];
                    volume = sum_volume_vector[i][j];
                    flag = false;
                }
                if (flag == false)
                    break;
            }
            if (flag == false)
                break;
        }
        k--;
    }*/
    best_weight = 0;
    best_count = 0;
    best_volume = 0;
    best_j = 0;

    for (int j = 0; j <= b; j++) {
        if (main_vector[n][j] > best_weight ||
            (main_vector[n][j] == best_weight && count[n][j] > best_count)) {
            best_weight = main_vector[n][j];
            best_count = count[n][j];
            best_volume = volume_main[n][j];
            best_j = j;
        }
    }
}

/**
 * Выводит результаты выбора артефактов, включая вес, объём и номера артефактов.
 * @param best_weight Лучший общий вес, найденный.
 * @param best_volume Лучший общий объём, найденный.
 * @param n Количество артефактов.
 * @param best_j Лучшая использованная грузоподъёмность в решении.
 * @param main_vector 2D-вектор, хранящий максимальные веса для подзадач.
 * @param weights Вектор весов артефактов (индексация с 1).
 */
void OutputResults(int best_weight, int best_volume, int n, int best_j,
                   const vector<vector<int>>& main_vector,
                   const vector<int>& weights) {
    cout << "weight: " << best_weight << " volume: " << best_volume << endl;
    cout << "artifact numbers: ";
    FindNumbers(main_vector, weights, n, best_j);
}

/**
 * Рекурсивно находит и выводит индексы выбранных артефактов.
 * @param main_vector 2D-вектор, хранящий максимальные веса для подзадач.
 * @param weights Вектор весов артефактов (индексация с 1).
 * @param i Текущий индекс строки в таблице динамического программирования (индекс артефакта).
 * @param j Текущий индекс столбца в таблице динамического программирования (текущая грузоподъёмность).
 */
// FIX ME неправильные входные дынные и нейминг
//void find_numbers(vector <vector <int>>& Mvector, int i, int j, vector <int>& Wvector)
void FindNumbers(const vector<vector<int>>& main_vector, const vector<int>& weights, int i, int j) {
    // FIX ME Неправильное условие проверки выбора предмета
    // if (Mvector[i][j] == 0) return;
    // if (Mvector[i - 1][j] == Mvector[i][j])
    //    find_numbers(Mvector, i - 1, j, Wvector);
    // else
    //{
    //    cout << i << " ";
    //    find_numbers(Mvector, i - 1, j, Wvector);
    //}
    if (i == 0 || j == 0) return;
    if (main_vector[i][j] == main_vector[i - 1][j]) {
        FindNumbers(main_vector, weights, i - 1, j);
    }
    else {
        cout << i << " ";
        FindNumbers(main_vector, weights, i - 1, j - weights[i]);
    }
}
