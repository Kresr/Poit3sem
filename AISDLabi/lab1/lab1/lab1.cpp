#include <iostream>
#include <ctime>

using namespace std;

int fibonacciIterative(int n) {
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "Введите значение N : ";
    cin >> n;

    clock_t startIterative = clock();
    int resultIterative = fibonacciIterative(n);
    clock_t endIterative = clock();
    double timeIterative = static_cast<double>(endIterative - startIterative) / CLOCKS_PER_SEC;

    clock_t startRecursive = clock();
    int resultRecursive = fibonacciRecursive(n);
    clock_t endRecursive = clock();
    double timeRecursive = static_cast<double>(endRecursive - startRecursive) / CLOCKS_PER_SEC;

    cout << "Линейный результат: " << resultIterative << endl;
    cout << "Рекурсивный результат " << resultRecursive << endl;

    cout << "Время работы цикла: " << timeIterative << " секунд." << endl;
    cout << "Время работы рекурсии: " << timeRecursive << " секунд." << endl;

    return 0;
}





