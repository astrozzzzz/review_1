//Археолог нашел N артефактов.Известны веса(сi) и объемы(di) артефактов.Нужно выбрать такое подмножество
//найденных вещей, чтобы суммарный их вес не превысил B кг, но был наиболее близок к B, а количество 
//взятых артефактов было как можно больше.Известно, что решение единственно.Укажите порядковые номера 
//вещей, которые надо взять.Исходные данные находятся в текстовом файле, в первой строке указаны N и B, 
//а во второй строке значения весов(в кг), в третьей объемы находок(в куб.см).Вывести так же суммарный 
//вес и суммарный объем результата.

#include "artifact_solver.h"
using namespace std;

/**
 * @brief Рекурсивно восстанавливает номера выбранных артефактов.
 *
 * @param main_vector Динамическая таблица с максимальными весами.
 * @param weights Вектор весов артефактов (индексация с 1).
 * @param i Текущий индекс артефакта.
 * @param j Текущий допустимый вес.
 */

// FIX ME неправильные входные дынные
//void find_numbers(vector <vector <int>>& Mvector, int i, int j, vector <int>& Wvector)

void find_numbers(vector<vector<int>>& main_vector, const vector<int>& weights, int i, int j)
{
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
    if (main_vector[i][j] == main_vector[i - 1][j]) 
    {
        find_numbers(main_vector, weights, i - 1, j);
    }
    else 
    {
        cout << i << " ";
        find_numbers(main_vector, weights, i - 1, j - weights[i]);
    }
}
/**
 * @brief Основная функция программы.
 * @return возвращает 0
 */
int main()
{
    // FIX ME ненужные переменные
    //int n, b, k, weight, volume, ind_i, ind_j;
    int n, b;
    ifstream stream;
    stream.open("a.txt");
    stream >> n;
    stream >> b;
    vector <int> weight_vector(n + 1);
    for (int i = 1; i <= n; i++)
        stream >> weight_vector[i];
    vector <int> volume_vector(n + 1);
    for (int i = 1; i <= n; i++)
        stream >> volume_vector[i];

    vector <vector <int>> main_vector(n + 1, vector <int>(b + 1, 0));
    // FIX ME нет учёта количества предметов и объёма
    //vector <vector <int>> sum_volume_vector(n + 1, vector <int>(b + 1, 0));
    vector<vector<int>> count(n + 1, vector<int>(b + 1, 0));
    vector<vector<int>> volume_main(n + 1, vector<int>(b + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            // FIX ME логика заполнения некорректная так как может привышать j
            //if (j >= weight_vector[i])
            //{
            //    main_vector[i][j] = main_vector[i - 1][j] + weight_vector[i];
            //    sum_volume_vector[i][j] = sum_volume_vector[i - 1][j] + volume_vector[i];
            //}
            //else
            //{
            //    main_vector[i][j] = main_vector[i - 1][j];
            //    sum_volume_vector[i][j] = sum_volume_vector[i - 1][j];
            //}

            int without_weight = main_vector[i - 1][j];
            int with_weight = (j >= weight_vector[i]) ? main_vector[i - 1][j - weight_vector[i]] + weight_vector[i] : 0;

            if (with_weight > without_weight) 
            {
                main_vector[i][j] = with_weight;
                count[i][j] = count[i - 1][j - weight_vector[i]] + 1;
                volume_main[i][j] = volume_main[i - 1][j - weight_vector[i]] + volume_vector[i];
            }
            else 
            {
                main_vector[i][j] = without_weight;
                count[i][j] = count[i - 1][j];
                volume_main[i][j] = volume_main[i - 1][j];
            }
        }
    }
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
    int best_weight = 0;
    int best_count = 0;
    int best_volume = 0;
    int best_j = 0;

    for (int j = 0; j <= b; j++) 
    {
        if (main_vector[n][j] > best_weight ||
            (main_vector[n][j] == best_weight && count[n][j] > best_count)) 
        {
            best_weight = main_vector[n][j];
            best_count = count[n][j];
            best_volume = volume_main[n][j];
            best_j = j;
        }
    }
    cout << "weight: " << best_weight << " volume: " << best_volume << endl;
    cout << "artifact numbers: ";
    find_numbers(main_vector, weight_vector, n, best_j);
}