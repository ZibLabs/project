#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

class date
{
public:
    int day;
    int month;
    int year;
    bool validDate = false;
    date(int day, int month, int year)
    {
        if (month >= 1 && month <= 12)
        {
            switch (month)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day >= 1 && day <= 31)
                {
                    this->day = day;
                    this->month = month;
                    this->year = year;
                    validDate = true;
                }
                else
                {
                    this->day = -1;
                    this->month = -1;
                    this->year = -1;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day >= 1 && day <= 30)
                {
                    this->day = day;
                    this->month = month;
                    this->year = year;
                    validDate = true;
                }
                else
                {
                    this->day = -1;
                    this->month = -1;
                    this->year = -1;
                }
                break;
            case 2:
                if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
                {
                    if (day >= 1 && day <= 29)
                    {
                        this->day = day;
                        this->month = month;
                        this->year = year;
                        validDate = true;
                    }
                    else
                    {
                        this->day = -1;
                        this->month = -1;
                        this->year = -1;
                    }
                }
                else
                {
                    if (day >= 1 && day <= 28)
                    {
                        this->day = day;
                        this->month = month;
                        this->year = year;
                        validDate = true;
                    }
                    else
                    {
                        this->day = -1;
                        this->month = -1;
                        this->year = -1;
                    }
                }
                break;
            default:
                break;
            }
        }

        else
        {
            this->day = -1;
            this->month = -1;
            this->year = -1;
        }
    }
    void to(date target)
    {
        if (!validDate || !target.validDate)
        {
            cout << "Invalid date(s)\n";
            return;
        }
            cout << "Days between: " << abs(target.day - day) << endl;        
    }
};

int main()
{
    date mainDate = date(20, 1, 2026);
    date goalDate = date(24, 1, 2024);
    mainDate.to(goalDate);
}