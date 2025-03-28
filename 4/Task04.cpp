//Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения, 
//не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
//Вывести значение целочисленного выражения, заданного в виде строки S.Выражение
//определяется следующим образом :
//<выражение> :: = <цифра> | (<выражение><знак><выражение>)
//< знак > :: = +| − | *

#include <iostream>
#include <string>
using namespace std;

int Calc(string s);

int Num(string s) {
    if (s[0] == '(' && s[s.length() - 1] == ')') {
        return Calc(s.substr(1, s.length() - 2));
    }
    else {
        return stoi(s);
    }
}

int Term(string s) {
    int i = s.length() - 1;
    int level = 0;
    int pos = -1;
    while (i >= 0) {
        if (s[i] == ')') {
            level++;
        }
        else if (s[i] == '(') {
            level--;
        }
        else if (level == 0 && s[i] == '*') {
            pos = i;
            break;
        }
        i--;
    }
    if (pos == -1) {
        return Num(s);
    }
    return Term(s.substr(0, pos)) * Num(s.substr(pos + 1));
}

int Calc(string s) {
    int i = s.length() - 1;
    int level = 0;
    int pos = -1;
    while (i >= 0) {
        if (s[i] == ')') {
            level++;
        }
        else if (s[i] == '(') {
            level--;
        }
        else if (level == 0 && (s[i] == '+' || s[i] == '-')) {
            pos = i;
            break;
        }
        i--;
    }

    if (pos == -1) {
        return Term(s);
    }

    char op = s[pos];
    if (op == '+') {
        return Calc(s.substr(0, pos)) + Term(s.substr(pos + 1));
    }
    if (op == '-') {
        return Calc(s.substr(0, pos)) - Term(s.substr(pos + 1));
    }

    return 0;
}

int main() {
    setlocale(0, "");
    string s;
    cout << "Введите строку вида - <цифра> | (<выражение><знак><выражение>), где знак - (+ | - | *):" << endl;
    cin >> s;
    cout << "Результат: " << Calc(s) << endl;
    return 0;
}