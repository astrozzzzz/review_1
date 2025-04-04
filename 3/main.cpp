#include "k_numbers.h"

using namespace std;

/**
 * @brief Основная функция программы для решения задачи о К-ичных числах.
 * @return Код завершения программы (0 при успехе, 1 при ошибке).
 */
int main() {
    // FIX ME объявление переменных без инициализации
    // int k, n;
    int k = 0;
    int n = 0;
    // FIX ME В оригинальном коде не было валидации данных
    if (!ReadInput(k, n) || !ValidateInput(k, n)) {
        return 1;
    }

    ComputeResult(k, n);

    return 0;
}