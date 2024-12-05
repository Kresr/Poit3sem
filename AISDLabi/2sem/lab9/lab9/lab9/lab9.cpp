#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <string>
#include <random>
using namespace std;

struct individual {
    string genome;       
    int adaptability;    
};

vector<vector<int>> graph = { 
    {INT_MAX, 25, 40, 31, 27, 16, 7, 9},
    {5, INT_MAX, 17, 30, 25, 4, 23, 23},
    {19, 15, INT_MAX, 6, 1, 19, 10, 8},
    {9, 50, 24, INT_MAX, 6, 6, 12, 11},
    {22, 8, 7, 10, INT_MAX, 19, 10, 9},
    {9, 50, 24, 6, 11, INT_MAX, 11, 18},
    {9, 50, 24, 6, 6, 14, INT_MAX, 10},
    {9, 50, 24, 6, 6, 12, 15, INT_MAX}
};

vector<int> nodes;          
int populationSize = 0;    
int childsNumber = 0;       
int mutationRate = 0;       
int evolutionCirclsNumber = 0;

int generateRandomNumber(int start, int end) {
    return start + rand() % (end - start);
}

bool isCorrect(const string& s, char ch) {
    for (char c : s) {
        if (c == ch) return false;
    }
    int from = s[s.size() - 1] - '0';
    int to = ch - '0';
    if (graph[from][to] == INT_MAX) return false;
    return true;
}

string mutatedGene(string genome) {
    while (true) {
        int g1 = generateRandomNumber(1, genome.size() - 1);
        int g2 = generateRandomNumber(1, genome.size() - 1);
        if (g1 != g2) {
            swap(genome[g1], genome[g2]);
            break;
        }
    }
    return genome;
}

string createGenome() {
    vector<int> n = nodes;
    string genome = "0";
    n.erase(n.begin());
    while (genome.size() < nodes.size()) {
        int idx = generateRandomNumber(0, n.size());
        int city = n[idx];
        if (isCorrect(genome, char(city + '0'))) {
            genome += char(city + '0');
            n.erase(n.begin() + idx);
        }
    }
    genome += genome[0];
    return genome;
}


int calculateAdaptability(const string& genome) {
    int distance = 0;
    for (size_t i = 0; i < genome.size() - 1; i++) {
        int from = genome[i] - '0';
        int to = genome[i + 1] - '0';
        if (graph[from][to] == INT_MAX) return INT_MAX;
        distance += graph[from][to];
    }
    return distance;
}

bool compareAdaptability(individual t1, individual t2) {
    return t1.adaptability < t2.adaptability;
}

void doGeneticAlgorithm() {
    vector<individual> population;

    for (int i = 0; i < populationSize; i++) {
        string genome = createGenome();
        int adaptability = calculateAdaptability(genome);
        population.push_back({ genome, adaptability });
    }

    sort(population.begin(), population.end(), compareAdaptability);

    for (int gen = 1; gen <= evolutionCirclsNumber; gen++) {
        cout << "\nПоколение " << gen << "\n";

        cout << "\nТекущая популяция:\n";
        cout << "Маршрут\t\tДлина\n";
        for (const auto& indiv : population) {
            cout << indiv.genome << "\t\t" << indiv.adaptability << "\n";
        }

        cout << "\nЛучший маршрут: " << population[0].genome
            << " Длина маршрута: " << population[0].adaptability << "\n";

        vector<individual> new_population;

        for (int i = 0; i < populationSize / 2; i += 2) {
            individual parent1 = population[i];
            individual parent2 = population[i + 1];

            string childGenome1 = parent1.genome;
            string childGenome2 = parent2.genome;

            if (generateRandomNumber(0, 100) < mutationRate) {
                childGenome1 = mutatedGene(childGenome1);
            }
            if (generateRandomNumber(0, 100) < mutationRate) {
                childGenome2 = mutatedGene(childGenome2);
            }

            new_population.push_back({ childGenome1, calculateAdaptability(childGenome1) });
            new_population.push_back({ childGenome2, calculateAdaptability(childGenome2) });
        }

        cout << "\nПотомки текущего поколения:\n";
        cout << "Маршрут\t\tДлина\n";
        for (const auto& indiv : new_population) {
            cout << indiv.genome << "\t\t" << indiv.adaptability << "\n";
        }

        population.insert(population.end(), new_population.begin(), new_population.end());
        sort(population.begin(), population.end(), compareAdaptability);
        population.resize(populationSize);

        if (population[0].adaptability == INT_MAX) {
            cout << "Решение не найдено. Завершение алгоритма.\n";
            break;
        }
    }

    cout << "\nНаиболее оптимальный маршрут: " << population[0].genome
        << " с длиной: " << population[0].adaptability << "\n";
}

void setupParameters() {
    cout << "Настройка параметров генетического алгоритма\n";

    cout << "Введите размер популяции: ";
    cin >> populationSize;

    while (populationSize <= 0) {
        cout << "Размер популяции должен быть положительным числом. Повторите ввод: ";
        cin >> populationSize;
    }

    cout << "Введите количество потомков при скрещивании (целое положительное число): ";
    cin >> childsNumber;

    while (childsNumber <= 0) {
        cout << "Количество потомков должно быть положительным числом. Повторите ввод: ";
        cin >> childsNumber;
    }

    cout << "Введите показатель мутации (в процентах от 0 до 100): ";
    cin >> mutationRate;

    while (mutationRate < 0 || mutationRate > 100) {
        cout << "Показатель мутации должен быть от 0 до 100. Повторите ввод: ";
        cin >> mutationRate;
    }

    cout << "Введите количество циклов эволюции (положительное число): ";
    cin >> evolutionCirclsNumber;

    while (evolutionCirclsNumber <= 0) {
        cout << "Количество циклов эволюции должно быть положительным числом. Повторите ввод: ";
        cin >> evolutionCirclsNumber;
    }

    cout << "\nНастройки завершены.\n";
}

void printGraph() {
    cout << "\nГраф (матрица смежности):\n";
    cout << "   ";
    for (int i = 0; i < graph.size(); i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << i << " ";
        for (int val : graph[i]) {
            if (val == INT_MAX) cout << "INF\t";
            else cout << val << "\t";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    nodes.resize(graph.size());
    for (int i = 0; i < nodes.size(); i++) nodes[i] = i;

    while (true) {
        cout << "\nМеню:\n"
            << "0. Показать Матрицу\n"
            << "1. Добавить город\n"
            << "2. Удалить город\n"
            << "3. Установить дорогу\n"
            << "4. Запустить алгоритм\n"
            << "5. Выход\n"
            << "Ваш выбор: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            printGraph();
        }
        else if (choice == 1) {
            for (auto& row : graph) row.push_back(INT_MAX);
            graph.emplace_back(graph.size() + 1, INT_MAX);
            nodes.push_back(nodes.size());
            cout << "Город добавлен. Теперь их " << graph.size() << ".\n";
        }
        else if (choice == 2) {
            int city;
            cout << "Введите номер города для удаления: ";
            cin >> city;
            if (city < 0 || city >= graph.size()) {
                cout << "Город с таким номером не существует.\n";
                continue;
            }
            graph.erase(graph.begin() + city);
            for (auto& row : graph) row.erase(row.begin() + city);
            nodes.erase(remove(nodes.begin(), nodes.end(), city), nodes.end());
            for (int i = 0; i < nodes.size(); i++) nodes[i] = i;
            cout << "Город " << city << " удален.\n";
        }
        else if (choice == 3) {
            int from, to, weight;
            cout << "Введите номера городов (откуда и куда) и расстояние: ";
            cin >> from >> to >> weight;
            if (from < 0 || from >= graph.size() || to < 0 || to >= graph.size()) {
                cout << "Неверные номера городов.\n";
                continue;
            }
            graph[from][to] = weight;
            graph[to][from] = weight;
            cout << "Дорога между " << from << " и " << to << " установлена с расстоянием " << weight << ".\n";
        }
        else if (choice == 4) {
            setupParameters();
            doGeneticAlgorithm();
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
