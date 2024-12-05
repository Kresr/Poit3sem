#include <iostream>
using namespace std;

const int V = 9;
void Dijkstra(int GR[V][V], int st);

void main()
{
	setlocale(LC_ALL, "Rus");
	int start;
	//матрица смежности графа
	int GR[V][V] = {
			{0,  7,  10, 0,  0,  0,  0 , 0,  0},//   A
			{7,  0,  0,  0,  0,  9,  27, 0,  0},//   B
			{10, 0,  0,  0,  31, 8,  0,  0,  0},//   C
			{0,  0,  0,  0,  32, 0,  0,  17, 21},//  D
			{0,  0,  31, 32, 0,  0,  0,  0,  0},//   E
			{0,  9,  8,  0,  0,  0,  0,  11, 0},//   F
			{0,  27, 0,  0,  0,  0,  0,  0,  15},//  G
			{0,  0,  0,  17, 0,  11, 0,  0,  15},//  H
			{0,  0,  0,  21, 0,  0,  15, 15, 0} };// I
	//       A	 B   C   D   E   F   G   H   I

	char symbols[40];
	bool pr = false;

	cout << "Введите начальную вершину: ";
	while (pr == false)
	{
		cin >> symbols;
		if (symbols[1] == '\0' && (symbols[0] == 'A' || symbols[0] == 'B' || symbols[0] == 'C' ||
			symbols[0] == 'D' || symbols[0] == 'E' || symbols[0] == 'F' ||
			symbols[0] == 'G' || symbols[0] == 'H' || symbols[0] == 'I'))
			pr = true;
		else
			cout << "Некорректный ввод. Повторите попытку. " << endl;
	}
	int letter = (int)symbols[0] - 65; // преобразование символа вершины в индекс
	Dijkstra(GR, letter);
}

void Dijkstra(int GR[V][V], int st)
{

	int length[V]; //массив для хранения кратчайших расстояний
	int index; // переменная для хранения индекса вершины с мин расстоянием
	int u; // текущая вершина
	int m = st + 1; //индекс начальной вершины для вывода
	bool visited[V];

	for (int i = 0; i < V; i++)
	{
		length[i] = INT_MAX;
		visited[i] = false;
	}

	length[st] = 0; // расстояние от начальной вершины до самой себя

	for (int count = 0; count < V - 1; count++) // поиск кратчайшего пути
	{
		int min = INT_MAX;

		for (int i = 0; i < V; i++)
			if (!visited[i] && length[i] <= min) // если не посещена и ее расстояние меньше текущего минимального
			{
				min = length[i];
				index = i;
			}

		u = index; // установка текущей вершины
		visited[u] = true;

		for (int i = 0; i < V; i++) // обновление расстояний до смежных вершин
			if (!visited[i] && GR[u][i] && length[u] != INT_MAX && length[u] + GR[u][i] < length[i])
				length[i] = length[u] + GR[u][i];
	}

	cout << "Длинна маршрутов: ";

	for (int i = 0; i < V; i++)
	{
		if (length[i] != INT_MAX)
			printf("Из вершины %c в %c : %d\n", (char)(m + 64), (char)(i + 65), length[i]);
		else // если вершина недоступна
			printf("Из вершины %c в %c : недоступен\n", (char)(m + 64), (char)(i + 65));
	}
}
