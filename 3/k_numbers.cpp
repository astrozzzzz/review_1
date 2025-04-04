/**
 * К - ичные числа.Среди чисел в системе счисления с основанием K(2≤K≤10) определить
 * сколько имеется чисел из N(1 < N < 20, N + K < 26) разрядов таких, что в их записи
 * содержится два и более подряд идущих нулей.Для того, чтобы избежать переполнения, ответ
 * представьте в виде вещественного числа.
*/
#include "k_numbers.h"

using namespace std;

/**
 * @brief
 * @return Возвращает true при успехе и false при еудаче.
 */

bool ReadInput(int& k, int& n) {
    cout << "Введите K (2<=K<=10) : ";
    if (!(cin >> k)) {
        cout << "Ошибка: K должно быть целым числом." << endl;
        return false;
    }

    cout << "Введите N (1<N<20, N+K<26) : ";
    if (!(cin >> n)) {
        cout << "Ошибка: N должно быть целым числом." << endl;
        return false;
    }
    return true;
}

/**
 * @brief Проверяет входные данные K и N на соответствие ограничениям и типу.
 * @param k Основание системы счисления.
 * @param n Количество разрядов.
 * @return true, если входные данные корректны, иначе false.
 */
bool ValidateInput(int k, int n) {
    if (k == 0 || n == 0) {
        cout << "Ошибка: K и N должны быть ненулевыми (возможно, введены некорректные данные)." << endl;
        return false;
    }
    if (k < 2 || k > 10) {
        cout << "Ошибка: K должно быть в диапазоне 2 <= K <= 10." << endl;
        return false;
    }
    if (n <= 1 || n >= 20) {
        cout << "Ошибка: N должно быть в диапазоне 1 < N < 20." << endl;
        return false;
    }
    if (n + k >= 26) {
        cout << "Ошибка: N + K должно быть меньше 26." << endl;
        return false;
    }
    return true;
}

/**
 * @brief Вычисляет количество чисел с двумя и более подряд идущими нулями.
 * @param k Основание системы счисления.
 * @param n Количество разрядов.
 * @return Количество чисел с двумя и более подряд идущими нулями.
 */
double ComputeResult(int k, int n) {
    // FIX ME непонятные названия переменных и нет инициализации
    // double nz, oz, tz;

    double non_zero_ending = k - 1; // Числа без ведущих нулей
    // FIX ME Для одного разряда (N=1) не существует чисел, заканчивающихся на ноль
    //oz = 1; Числа, заканчивающиеся на 0 (без подряд идущих нулей)
    double one_zero_ending = 0;     // Числа, заканчивающиеся на 0 (без подряд идущих нулей)
    double two_or_more_zeros = 0;     // Числа, содержащие подряд идущие нули

    for (int i = 2; i <= n; i++) {
        // FIX ME Переменные _nz, _oz, _tz переименованы в temp_nz, temp_oz, temp_tz, чтобы
        // соответствовать стилю snake_case и быть более описательными.
        //double _nz = nz;
        //double _oz = oz;
        //double _tz = tz;
        double temp_non_zero = non_zero_ending;
        double temp_one_zero = one_zero_ending;
        double temp_two_or_more = two_or_more_zeros;

        non_zero_ending = (temp_non_zero + temp_one_zero) * (k - 1);
        one_zero_ending = temp_non_zero;
        two_or_more_zeros = temp_two_or_more * k + temp_one_zero;
    }

    cout << "Числа без двух подряд идущих нулей: " << fixed << non_zero_ending + one_zero_ending << "\n";
    cout << "Числа с двумя и более подряд идущими нулями: " << fixed << two_or_more_zeros << "\n";

    return two_or_more_zeros;
}

