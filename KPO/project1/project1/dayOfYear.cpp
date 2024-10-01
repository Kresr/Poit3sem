#include "stdafx.h"

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