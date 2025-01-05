#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace chrono;

int randomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

vector<int> generateBoxes(int n) {
    vector<int> boxes(n);
    for (int i = 0; i < n; ++i) {
        boxes[i] = i + 1;
    }
    for (int i = 0; i < n; ++i) {
        int j = randomNumber(0, n - 1);
        swap(boxes[i], boxes[j]);
    }
    return boxes;
}

bool randomChoice(const vector<int>& boxes, int prisonerNumber) {
    vector<bool> visited(boxes.size(), false);
    for (int i = 0; i < 50; ++i) {
        int boxIndex;
        do {
            boxIndex = randomNumber(0, boxes.size() - 1);
        } while (visited[boxIndex]);
        visited[boxIndex] = true;
        if (boxes[boxIndex] == prisonerNumber) {
            return true;
        }
    }
    return false;
}

bool optimalChoice(const vector<int>& boxes, int prisonerNumber) {
    int nextBox = prisonerNumber - 1;
    for (int i = 0; i < 50; ++i) {
        if (boxes[nextBox] == prisonerNumber) {
            return true;
        }
        nextBox = boxes[nextBox] - 1;
    }
    return false;
}

void runExperiment(int n, int rounds) {
    int randomWins = 0;
    int optimalWins = 0;
    auto randomStart = high_resolution_clock::now();
    for (int r = 0; r < rounds; ++r) {
        vector<int> boxes = generateBoxes(n);
        bool randomSuccess = true;
        for (int prisoner = 1; prisoner <= n; ++prisoner) {
            if (!randomChoice(boxes, prisoner)) {
                randomSuccess = false;
                break;
            }
        }
        if (randomSuccess) randomWins++;
    }
    auto randomEnd = high_resolution_clock::now();
    auto randomDuration = duration_cast<milliseconds>(randomEnd - randomStart);

    auto optimalStart = high_resolution_clock::now();
    for (int r = 0; r < rounds; ++r) {
        vector<int> boxes = generateBoxes(n);
        bool optimalSuccess = true;
        for (int prisoner = 1; prisoner <= n; ++prisoner) {
            if (!optimalChoice(boxes, prisoner)) {
                optimalSuccess = false;
                break;
            }
        }
        if (optimalSuccess) optimalWins++;
    }
    auto optimalEnd = high_resolution_clock::now();
    auto optimalDuration = duration_cast<milliseconds>(optimalEnd - optimalStart);

    cout << "Результаты после " << rounds << " раундов:" << endl;
    cout << "Случайный алгоритм: " << randomWins << " успешных исходов, время: " << randomDuration.count() << " мс" << endl;
    cout << "Оптимизированный алгоритм: " << optimalWins << " успешных исходов, время: " << optimalDuration.count() << " мс" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(nullptr));

    int n = 100;
    int rounds;

    cout << "Введите количество раундов для сравнения алгоритмов: ";
    cin >> rounds;

    runExperiment(n, rounds);

    return 0;
}
