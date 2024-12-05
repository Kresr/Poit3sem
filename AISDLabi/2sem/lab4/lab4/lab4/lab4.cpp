#include <iostream>
#include <climits>
using namespace std;

int C[6][6] = {
    {0, 28, 21, 59, 12, 27},       // 1
    {7, 0, 24, INT_MAX, 21, 9},    // 2
    {9, 32, 0, 13, 11, INT_MAX},   // 3
    {8, INT_MAX, 5, 0, 16, INT_MAX}, // 4
    {14, 13, 15, 10, 0, 22},       // 5
    {15, 18, INT_MAX, INT_MAX, 6, 0} // 6
};

int S[6][6];

void FloydWarshall();
void PrintPath(int start, int end);

int main() {
    setlocale(LC_ALL, "Rus");

    // Инициализация матрицы путей
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            S[i][j] = j;
        }
    }

    FloydWarshall();

    int start, end;
    cout << "Введите начальную вершину (1-6): ";
    cin >> start;
    cout << "Введите конечную вершину (1-6): ";
    cin >> end;

    if (start < 1 || start > 6 || end < 1 || end > 6) {
        cout << "Неверный ввод вершин! Допустимые значения от 1 до 6." << endl;
        return 1;
    }

    cout << "Кратчайший путь: ";
    PrintPath(start - 1, end - 1);
    cout << end << endl;

    return 0;
}

void FloydWarshall() {
    for (int m = 0; m < 6; m++)
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                if (C[i][j] > C[i][m] + C[m][j]) {
                    C[i][j] = C[i][m] + C[m][j];
                    S[i][j] = S[i][m]; // обновляем путь через промежуточную вершину
                }

    printf("Расстояния:\n");
    for (int i = 0; i < 6; i++) {
        for (int k = 0; k < 6; k++) {
            if (C[i][k] == INT_MAX)
                printf("∞\t");
            else
                printf("%d\t", C[i][k]);
        }
        printf("\n");
    }

    printf("Матрица путей:\n");
    for (int i = 0; i < 6; i++) {
        for (int k = 0; k < 6; k++) {
            printf("%d\t", S[i][k] + 1);
        }
        printf("\n");
    }
}

void PrintPath(int start, int end) {
    if (start == end) {
        return;
    }

    if (S[start][end] == end) {
        cout << start + 1 << "-";
        return;
    }

    if (S[start][end] == start) {
        cout << "Ошибка: зацикливание в пути!" << endl;
        return;
    }

    PrintPath(start, S[start][end]);
    cout << S[start][end] + 1 << "-";
}
