#include <string>
#include <iostream>
#include <chrono>

using namespace std;

#define INT_MAX 32767

int NUM;
struct arr {
	string str = "\0";
	int num = 0;
	arr* next = NULL;
};
int hash_f(string str, int* rand8) {
	int sum = 0;
	for (int i = 0; i < str.length(); i++) sum += str[i];
	return sum % NUM;
}
void output(arr* tab, int size) {
	setlocale(LC_ALL, "RUS");
	for (int i = 0; i < size; i++) { // пока не выведем весь массив
		arr* ptr = &tab[i];
		do {
			if (ptr->str[0] == '\0') {
				cout << "Empty\n";
				break;
			}
			else
				cout << "name: " << ptr->str << "\tnumber: " << ptr->num << endl;
		} while (ptr = ptr->next);
	}
}
void dlt(arr* tab, int size, int num, int* rand8) {
	int k = hash_f(to_string(num), rand8); // вычисляем ключ элемента
	while (k > size - 1) k -= size; // уменьшаем ключ
	arr* ptr = &tab[k];
	if (ptr->num == num) { // если элемент найден
		if (ptr->next) {
			ptr->num = ptr->next->num; // записываем ключ
			ptr->str = ptr->next->str; //имя
			ptr->next = ptr->next->next; // меняем указатель на следующий элемент от удалённого
		}
		else {
			ptr->num = 0;
			ptr->str = '\0';
		}
		return;
	}
	if (ptr->num) { // если список не пуст
		arr* ptr_prev = new arr;
		if (ptr->num == num) {
			ptr_prev->next = ptr->next;
			delete ptr;
			return;
		}
	}
	cout << "Элемента нет\n";
	return;
}
void input(arr* tab, int size, string str, int num, int* rand8) {
	int k = hash_f(to_string(num), rand8); // ищем ключ для элемента в хеш-функции
	while (k > size - 1)
		k -= size; // уменьшаем ключ, чтобы влез в размерность
	arr* ptr = &tab[k];
	if (!ptr->num) { // если элемент пуст
		ptr->next = NULL; // следующий элемент NULL
		ptr->str = str; // записываем имя
		ptr->num = num; // записываем ключ
	}
	else {
		arr* current = ptr;
		while (current->next) {
			current = current->next; // переходим к концу списка
		}
		arr* p = new arr;
		p->next = NULL; // для следующего элемента p установили NULL
		p->str = str; // имя
		p->num = num; // ключ
		current->next = p; // для current установили следующим элементом p
	}
}

void search(arr* tab, int size, int num, int* rand8) {
	int k = hash_f(to_string(num), rand8);
	while (k > size - 1)
		k -= size; // уменьшение ключа до размера массива
	arr* ptr = &tab[k];
	if (ptr->num) {
		while (ptr->next && ptr->num != num) {
			ptr = ptr->next;
		}
		if (ptr->num == num) {
			cout << "Ключ: " << ptr->num << "\tИмя: " << ptr->str << endl;
			return;
		}
		cout << "error\n";
		exit(1);
	}
	cout << "Элемента нет\n";
	return;
}
void main() {
	setlocale(LC_ALL, "ru");
	int size;
	cout << "Введите размер таблицы: "; cin >> size;
	NUM = size;
	int clearMas[256] = { 0 };
	arr* mas = new arr[size];
	int choise;
	do {
		cout << "1 - Вывод хеш-таблицы\n2 - Добавление элемента\n3 - Поиск элемента\n4 - Удаление\n0 - Выход\n";
		cin >> choise;
		switch (choise) {
		case 1: {
			output(mas, size);
			break;
		}
		case 2: {
			string str;
			int num;
			cout << "Введите имя: ";
			cin.ignore();
			getline(cin, str);
			cout << "Введите номер телефона: ";
			cin >> num;
			if (0 < num < INT_MAX)
				input(mas, size, str, num, clearMas);
			else
				cout << "Некорректный номер\n";
			break;
		}
		case 3: {
			cout << "Введите ключ: ";
			int num;
			cin >> num;
			cin.ignore();
			auto start = chrono::high_resolution_clock::now();
			search(mas, size, num, clearMas);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<float>duration = end - start;
			cout << "Расчетное время: " << duration.count() << " секунд" << endl;
			break;
		}
		case 4: {
			cout << "Введите ключ: ";
			int num;
			cin >> num;
			dlt(mas, size, num, clearMas);
		}
		default:
			break;
		}
	} while (choise);
}