#include "stdafx.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    int day, month, year;

    do {
        cout << "Введите день, месяц и год (ДД ММ ГГГГ): ";
        cin >> day >> month >> year;

        if (!isValidDate(day, month, year)) {
            cout << "Некорректная дата. Пожалуйста, введите дату заново." << endl;
        }

    } while (!isValidDate(day, month, year));

    bool leapYear = isLeapYear(year);
    int dayCount = dayOfYear(day, month, year);

    cout << "Год " << (leapYear ? "високосный" : "не високосный") << endl;
    cout << "Порядковый номер дня в году: " << dayCount << endl;

    int birthdayDay, birthdayMonth;

    cout << "Введите день и месяц своего рождения (ДД ММ): ";
    cin >> birthdayDay >> birthdayMonth;

    while (!isValidDate(birthdayDay, birthdayMonth, year)) {
        cout << "Некорректная дата. Пожалуйста, введите день и месяц рождения заново: ";
        cin >> birthdayDay >> birthdayMonth;
    }

    int daysInYear = leapYear ? 366 : 365;

    int daysUntilNextBirthday = daysUntilBirthday(dayCount, dayOfYear(birthdayDay, birthdayMonth, year), daysInYear);
    cout << "Дней до ближайшего дня рождения: " << daysUntilNextBirthday << endl;

    return 0;
}




