#include <iostream>
using namespace std;

typedef unsigned char day;
typedef unsigned char month;
typedef unsigned short year;

struct Date
{
	day dd;
	month mm;
	year yyyy;
};

bool operator > (Date d1, Date d2) {
	if (d1.yyyy > d2.yyyy)
		return true;
	else if (d1.yyyy == d2.yyyy) {
		if (d1.mm > d2.mm)
			return true;
		else
			if (d1.dd > d2.dd)
				return true;
	}
	else
		return false;
}

bool operator < (Date d1, Date d2) {
	if (d1.yyyy < d2.yyyy)
		return true;
	else if (d1.yyyy == d2.yyyy) {
		if (d1.mm < d2.mm)
			return true;
		else
			if (d1.dd < d2.dd)
				return true;
			else
				return false;
	}
	else
		return false;
}
bool operator == (Date d1, Date d2) {
	if (d1.yyyy == d2.yyyy && d1.mm == d2.mm && d1.dd == d2.dd)
		return true;
	else
		return false;
}

int main() {
	setlocale(LC_ALL, "Russian");

	Date date1 = { 7, 1, 1980 };
	Date date2 = { 7, 2, 1993 };
	Date date3 = { 7, 1, 1980 };

	if (date1 < date2)
		cout << "Истина" << endl;
	else
		cout << "Ложь" << endl;

	if (date1 > date2)
		cout << "Истина" << endl;
	else
		cout << "Ложь" << endl;

	if (date1 == date2)
		cout << "Истина" << endl;
	else
		cout << "Ложь" << endl;

	if (date1 == date3)
		cout << "Истина" << endl;
	else
		cout << "Ложь" << endl;
}
