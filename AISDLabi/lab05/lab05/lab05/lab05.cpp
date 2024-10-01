#include <iostream>
#include "Stack.h"
#include <string>
using namespace std;
bool prov(const string& s, int& count) {
    Stack* stack;
    stack = NULL;
    for (char c : s) {
        switch (c) {
        case '(':
            push(')', stack);
            count++;
            break;
        case '[':
            push(']', stack);
            count++;
            break;
        case '{':
            push('}', stack);
            count++;
            break;
        case ')':
        case ']':
        case '}':
            if (isEmpty(stack) || top(stack) != c) {
                if (c == ')' || c == '}' || c == ']')
                    count++;
                return false;
            }
            pop(stack);
            break;
        default:
            break;
        }
    }
    return isEmpty(stack);
}
void test(const string& s, int& count) {
    if (prov(s, count) && count > 0)
        cout << "Скобки расставлены верно" << endl << endl;
    if (count == 0)
        cout << "Скобки отсутствуют" << endl << endl;
    else
        if (!prov(s, count) && count > 0)
            cout << "Скобки расставлены неверно" << endl << endl;
}
void main() {
    setlocale(LC_ALL, "rus");
    while (true) {
        int count = 0;
        cout << "Введите строку с клавиатуры: ";
        string str;
        getline(cin, str);
        test(str, count);
    }
}

