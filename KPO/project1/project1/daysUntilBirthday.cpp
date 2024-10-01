#include "stdafx.h"
int daysUntilBirthday(int currentDay, int birthdayDay, int daysInYear) {
    if (currentDay <= birthdayDay) {
        return birthdayDay - currentDay;
    }
    else {
        return daysInYear - (currentDay - birthdayDay);
    }
}