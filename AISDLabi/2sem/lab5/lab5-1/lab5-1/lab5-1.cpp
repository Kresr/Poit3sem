#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define V 8 

int minKey(const vector<int>& key, const vector<bool>& inMST) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMST(const vector<int>& parent, const vector<vector<int>>& graph) {
    cout << "Ребро \tВес\n";
    for (int i = 1; i < V; i++) {
        cout << "V" << parent[i] + 1 << " - V" << i + 1 << "\t" << graph[i][parent[i]] << endl;
    }
}

// Алгоритм Прима
void primMST(const vector<vector<int>>& graph) {
    vector<int> parent(V); // Массив для хранения 
    vector<int> key(V, INT_MAX); // Минимальные веса для вершин
    vector<bool> inMST(V, false); // Включены ли вершины в остовное дерево

    key[0] = 0; // Начинаем с первой вершины
    parent[0] = -1; // Первая вершина - корень остовного дерева

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, inMST); // Выбираем вершину с минимальным весом
        inMST[u] = true; // Включаем её в остовное дерево

        // Обновляем ключи и родителей соседних вершин
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main() {
    setlocale(LC_ALL, "Rus");
    vector<vector<int>> graph = {
        //   1  2  3  4  5  6  7  8
            {0, 2, 0, 8, 2, 0, 0, 0}, // V1
            {2, 0, 3, 10, 5, 0, 0, 0}, // V2
            {0, 3, 0, 0, 12, 0, 0, 7}, // V3
            {8, 10, 0, 0, 14, 3, 1, 0}, // V4
            {2, 5, 12, 14, 0, 11, 4, 8}, // V5
            {0, 0, 0, 3, 11, 0, 6, 0}, // V6
            {0, 0, 0, 0, 4, 6, 0, 9}, // V7
            {0, 0, 7, 0, 8, 0, 9, 0}  // V8
    };

    primMST(graph);

    return 0;
}
