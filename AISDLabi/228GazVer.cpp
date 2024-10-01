#include <iostream>
#include <cstdio>
using namespace std;

void print_steps(int N) {
    int step = 1;
    while (N > 0) {
        cout << N << endl;
        step++;

        if (N > 1) {
            if (N % 2 == 0) {
                N /= 2;
            }
            else {
                N = (N + 1) / 2;
            }
        }
        else {
            break; 
        }
    }

    cout << "Шаги бинарного поиска:" << endl;
    for (int i = step; i >= 0; i--) {
        printf("%d\n", 1 << i);
    }
}


int main() {
    setlocale(LC_ALL, "RUS");
    int N;

    do {
        cout << "Введите N: ";
        cin >> N;

        if (N <= 0) {
            cout << "Zachem vam 0?" << endl;
        }

    } while (N <= 0);

    int low = 1, high = N, steps = 1, mid;

    while (low <= high) {
        steps++;
        mid = (low + high) / 2;

        cout << mid << endl;

        cout << "Ваш ответ (1 - 'мало', 2 - 'много', 3 - 'угадал'): ";
        int user_response;
        cin >> user_response;

        switch (user_response) {
        case 1:
            low = mid + 1;
            break;
        case 2:
            high = mid - 1;
            break;
        case 3:
            goto end;
        default:
            cout << "Некорректный ответ. Введите 1 - 'мало', 2 - 'много' или 3 - 'угадал'." << endl;
            break;
        }
    }

end:

    cout << "Максимальное количество шагов = " << steps << endl;
    print_steps(N);

    return 0;
}
