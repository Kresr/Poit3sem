#include <iostream>
#include <string>

using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isLeapYear(year)) {
        daysInMonth[2] = 29;
    }

    return day <= daysInMonth[month];
}

int dayOfYear(int day, int month, int year) {
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int dayCount = day;
    for (int i = 1; i < month; ++i) {
        dayCount += daysInMonth[i];
    }

    if (month > 2 && isLeapYear(year)) {
        dayCount += 1;
    }

    return dayCount;
}

int daysUntilBirthday(int currentDay, int birthdayDay, int daysInYear) {
    if (currentDay <= birthdayDay) {
        return birthdayDay - currentDay;
    }
    else {
        return daysInYear - (currentDay - birthdayDay);
    }
}

string getMonthName(int month) {
    string monthNames[] = { "", "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
    return monthNames[month];
}

void dateForOrdinalNumber(int ordinalNumber, int year) {
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int month = 1;

    int daysInYear = isLeapYear(year) ? 366 : 365;

    if (ordinalNumber < 1 || ordinalNumber > daysInYear) {
        cout << "Ошибка: порядковый номер дня в году должен быть от 1 до " << daysInYear << endl;
        return;
    }

    while (ordinalNumber > daysInMonth[month]) {
        ordinalNumber -= daysInMonth[month];
        month++;
    }

    if (month == 2 && isLeapYear(year)) {
        ordinalNumber -= 1;
    }

    cout << "Дата для порядкового номера в году " << year << ": " << ordinalNumber << " " << getMonthName(month) << " " << year << endl;
}

void specialEventForOrdinalNumber(int ordinalNumber, int year, int birthdayDay, int birthdayMonth) {
    bool leapYear = isLeapYear(year);

    if (leapYear && ordinalNumber == 152) {
        cout << "Сегодня первый день лета! Добро пожаловать в летний сезон!" << endl;
    }
    else if (!leapYear && ordinalNumber == 151) {
        cout << "Сегодня первый день лета! Добро пожаловать в летний сезон!" << endl;
    }
    else if ((ordinalNumber == 256 && !leapYear) || (ordinalNumber == 257 && leapYear)) {
        cout << "Сегодня День программиста! Поздравляю вас с этим замечательным днём!" << endl;
    }
    else {
        cout << "Сегодня обычный день." << endl;
    }
}



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

    int ordinalNumber;
    cout << "Введите порядковый номер дня в году: ";
    cin >> ordinalNumber;

    dateForOrdinalNumber(ordinalNumber, year);
    specialEventForOrdinalNumber(ordinalNumber, year, birthdayDay, birthdayMonth);

    return 0;
}







