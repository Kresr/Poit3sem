#include <iostream>
using namespace std;
void main() {
	setlocale(LC_ALL, "Rus");
	while (true) {
		float num;
		cin >> num;
		if (num == 0) {
			cout << "Ноль ни положительный, ни отрицательный" << endl;
		}
		else {
			auto res = [num] {
				if (num > 0)
					return true;
				if (num < 0)
					return false;
				};
			cout << "Функция вернула: " << res() << endl;
		}
	}
}