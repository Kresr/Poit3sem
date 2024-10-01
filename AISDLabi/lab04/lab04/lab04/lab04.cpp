#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");


	int N, tmp, step;
	int i, j, k;

	do
	{
		cout << "Введите количество товаров: ";
		cin >> N;

		if (N > 10000 || N < 0)
			cout << "Некорректный ввод";
	} while (N > 10000 || N < 0);

	int size = N;

	int* productsList = new int[size]; //Весь список цен

	for (i = 0; i < size; i++)
		productsList[i] = (rand() % 100 + 1);


	//-------------------------------------------  Сортировка массива

	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
		{
			tmp = productsList[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < productsList[j - step])
					productsList[j] = productsList[j - step];
				else
					break;
			}
			productsList[j] = tmp;
		}

	//-------------------------------------------
	//------------------------------------------- Создание 2-х других массивов для деления цен на > чем среднее и < чем среднее 
	int* lowestCost = new int[size / 2];  //Список цен меньших половины
	int* highestCost = new int[size / 2]; //Список цен больших половины

	for (i = 0; i < size; i++)
		if (i < size / 2)
			lowestCost[i] = productsList[i];
		else
			highestCost[i - size / 2] = productsList[i];

	//-------------------------------------------
	//-------------------------------------------

	int* endList = new int[size]; //Конечный список цен благоприятный для магазина

	for (i = 0, j = 0, k = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			endList[i] = highestCost[j];
			j++;
		}
		else
		{
			endList[i] = lowestCost[k];
			k++;
		}
	}


	//-------------------------------------------

	int sum = 0; //итоговая цена чека

	for (i = 0; size % 2 == 1 ? i < size / 2 + 1 : i < size / 2; i++)
		sum += highestCost[i];



	cout << "\nНачальные цены\n";
	for (i = 0; i < size; i++)
	{
		cout << productsList[i] << ' ';
	}

	cout << "\nМинимальные цены\n";
	for (i = 0; i < size / 2; i++)
		cout << lowestCost[i] << ' ';

	cout << "\nМаксимальные цены\n";
	for (i = 0; size % 2 == 1 ? i < size / 2 + 1 : i < size / 2; i++)
		cout << highestCost[i] << ' ';

	cout << "\n\nКонечный лист цен\n";
	for (i = 0; i < size; i++)
		cout << endList[i] << ' ';

	cout << "\n\nКонечная цена чека = " << sum << "\n\n";



	return 0;
}