//Археолог нашел N артефактов.Известны веса(сi) и объемы(di) артефактов.Нужно выбрать такое подмножество
//найденных вещей, чтобы суммарный их вес не превысил B кг, но был наиболее близок к B, а количество 
//взятых артефактов было как можно больше.Известно, что решение единственно.Укажите порядковые номера 
//вещей, которые надо взять.Исходные данные находятся в текстовом файле, в первой строке указаны N и B, 
//а во второй строке значения весов(в кг), в третьей объемы находок(в куб.см).Вывести так же суммарный 
//вес и суммарный объем результата.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
void find_numbers(vector <vector <int>> &Mvector, int i, int j, vector <int> &Wvector)
{
    if (Mvector[i][j] == 0)
        return;
    if (Mvector[i-1][j] == Mvector[i][j])
        find_numbers(Mvector, i - 1, j, Wvector);
    else
    {
        cout << i << " ";
        find_numbers(Mvector, i - 1, j, Wvector);
    }
}
int main()
{
    int n, b, k, weight, volume, ind_i, ind_j;
    ifstream stream;
    stream.open("a.txt");
    stream >> n;
    stream >> b;
    vector <int> weight_vector(n+1);
    for (int i = 1; i <= n; i++)
        stream >> weight_vector[i];
    vector <int> volume_vector(n+1);
    for (int i = 1; i <= n; i++)
        stream >> volume_vector[i];
    vector <vector <int>> main_vector(n+1, vector <int>(b+1, 0));
    vector <vector <int>> sum_volume_vector(n+1, vector <int>(b+1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            if (j >= weight_vector[i])
            {
                main_vector[i][j] = main_vector[i-1][j] + weight_vector[i];
                sum_volume_vector[i][j] = sum_volume_vector[i-1][j] + volume_vector[i];
            }
            else
            {
                main_vector[i][j] = main_vector[i-1][j];
                sum_volume_vector[i][j] = sum_volume_vector[i-1][j];
            }
        }
    }
    k = b;
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
    }
    cout << "weight: " << weight << " volume: " << volume << endl;
    cout << "artifact numbers: ";
    find_numbers(main_vector, ind_i, ind_j, weight_vector);
}
