#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

int counter = 0;

void Hano(int n, int source, int target, vector<int>& sticks) {
    if (n == 0) return;
    if (n == 1) {
        counter++;
        cout << "Переместить диск с " << source << " на " << target << endl;
        return;
    }

    if (sticks.size() == 3) {
        int temp = 6 - source - target;
        Hano(n - 1, source, temp, sticks);
        Hano(1, source, target, sticks);
        Hano(n - 1, temp, target, sticks);
    }
    else {
        vector<int> remaining_sticks;
        for (int stick : sticks) {
            if (stick != source && stick != target) {
                remaining_sticks.push_back(stick);
            }
        }

        int mid_stick = remaining_sticks[0];

        int k = n - 1; 

        Hano(k, source, mid_stick, sticks);

        Hano(1, source, target, sticks);

        Hano(k, mid_stick, target, sticks);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    int n, num_sticks, source, target;

    while (true) {

        cout << "Введите количество стержней: ";
        cin >> num_sticks;
        if (cin.fail() || num_sticks < 3) {
            cout << "\n Данные введены неверно, попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

        cout << "\nВведите число дисков: ";
        cin >> n;
        if (cin.fail() || n <= 0 || n > 1000) {
            cout << "\n Данные введены неверно, попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

        cout << "\nВведите номер стержня, с которого нужно переместить диски (1 - " << num_sticks << "): ";
        cin >> source;
        if (cin.fail() || source < 1 || source > num_sticks) {
            cout << "\n Данные введены неверно, попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

        cout << "\nВведите номер стержня, на который нужно переместить диски (1 - " << num_sticks << ", не равный " << source << "): ";
        cin >> target;
        if (cin.fail() || target < 1 || target > num_sticks || target == source) {
            cout << "\n Данные введены неверно, попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

        vector<int> sticks(num_sticks);
        for (int i = 0; i < num_sticks; i++) {
            sticks[i] = i + 1;
        }

        counter = 0;

        auto start = chrono::high_resolution_clock::now();
        Hano(n, source, target, sticks);  
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;

        cout << "\nВремя выполнения: " << duration.count() << " секунд" << endl;
        cout << "Количество шагов: " << counter << endl;
        break;
    }

    system("pause");
    return 0;
}