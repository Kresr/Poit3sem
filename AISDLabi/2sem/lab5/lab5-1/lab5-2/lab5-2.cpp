#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E; // V - количество вершин, E - количество рёбер
    vector<Edge> edges; // Список всех рёбер
};

struct Subset {
    int parent;
    int rank;
};

// Функция для поиска корня вершины
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Функция для объединения двух подмножеств
void Union(vector<Subset>& subsets, int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    }
    else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    }
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Функция для реализации алгоритма Краскала
void KruskalMST(Graph& graph) {
    vector<Edge> result;
    int e = 0;

    // Сортируем рёбра по возрастанию их весов
    sort(graph.edges.begin(), graph.edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
        });

    // Выделяем память для представления V подмножеств
    vector<Subset> subsets(graph.V);
    for (int v = 0; v < graph.V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Проходим по отсортированным рёбрам
    for (Edge& nextEdge : graph.edges) {
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // Если включение этого ребра не создаёт цикл, добавляем его в результат
        if (x != y) {
            result.push_back(nextEdge);
            Union(subsets, x, y);
            e++;
        }

        // Если мы уже добавили V-1 рёбер, то минимальное остовное дерево готово
        if (e == graph.V - 1)
            break;
    }

    // Вывод минимального остовного дерева
    cout << "Ребро \tВес\n";
    for (Edge& edge : result) {
        cout << "V" << edge.src + 1 << " - V" << edge.dest + 1 << "\t" << edge.weight << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    Graph graph;
    graph.V = 8;
    graph.E = 16;

    graph.edges = {
        {0, 1, 2}, {0, 3, 8}, {1, 3, 10}, {1, 4, 5},
        {0, 4, 2}, {2, 4, 12}, {2, 7, 7}, {3, 5, 3},
        {4, 5, 11}, {4, 7, 8}, {4, 6, 4}, {5, 6, 6},
        {6, 7, 9}, {3, 4, 14}, {3, 6, 1}, {1, 2, 3}
    };

    KruskalMST(graph);

    return 0;
}
