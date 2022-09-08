const int main_date = 6;
const int main_year = 2012;
const int main_month = 0;
int day_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

bool leap_year(int year) {
    if (((year % 400 == 0) || (year % 100 != 0)) && (year % 4 == 0)) {
        return true;
    }
    else {
        return false;
    }
}

int write_day(int day, int month, int year) {
    int days = -1;
    while (year > main_year) {
        if (leap_year(year)) {
            days += 366;
        }
        else {
            days += 365;
        }
        --year;
    }
    while (year < main_year) {
        if (leap_year(year)) {
            days += 366;
        }
        else {
            days += 365;
        }
        ++year;
    }

    for (int ii = 0; ii < month; ++ii) {
        if (leap_year(year) && ii == 1) {
            days += 29;
        }
        else {
            days += day_in_month[ii];
        }
    }

    days += day - 1;

    return days % 7;
}