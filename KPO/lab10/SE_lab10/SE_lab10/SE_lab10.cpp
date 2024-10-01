#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main() {
	setlocale(LC_ALL, "Russian");
	vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

	//определить количество целых чисел равных заданному
	int target1 = 3;
	int num_items1 = count(v.begin(), v.end(), target1); //выводит числа == target1
	cout << "Число: " << target1 << ", количество: " << num_items1 << '\n';

	//лямбда-выражение для подсчёта элементов, кратных 3
	int num_items3 = count_if(v.begin(), v.end(), [](int i) {
		return i % 3 == 0;
		}); //Возвращает количество элементов в группе, которые удовлетворяют условию
	cout << "Количество элементов, кратных 3: " << num_items3 << '\n';

	cout << endl << "Лямбда, захват переменных" << endl;
	//лямбда-выражение, захват переменных
	for (auto i : v)[i]() {
		if (i % 3 == 0)
			cout << i << " ";
		}();

		cout << endl << "Лямбда с параметрами" << endl;
		//Вывод значений кратных 3, значение будем передавать как параметр у обычной функции
		for (auto i : v)[](auto i) {
			if (i % 3 == 0)
				cout << i << " ";
			}(i);

			cout << endl << "Лямбда без параметров" << endl;
			//Вывод значений кратных 3
			//Значение передаются через захват переменных, при этом пропустим скобки для добавления параметров
			for (auto i : v)[i] {
				if (i % 3 == 0)
					cout << i << " ";
				}();
				cout << endl;
}