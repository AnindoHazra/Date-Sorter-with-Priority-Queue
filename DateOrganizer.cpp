/**
 * A testbed for a binary heap implementation of a priority queue to sort
 * Gregorian dates using various comparators
 * @author Duncan, Anindo Hazra
 * @see Date.h, PQueue.h
 * <pre>
 * Date: 25 September 2023
 * Course: csc 3102
 * File: DateOrganizer.cpp
 * Instructor: Dr. Duncan
 * </pre>
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <functional>
#include <string>
#include <sstream>
#include "PQueue.cpp"
#include "Date.h"

using namespace std;

/**
 * Gives the integer value equivalent to the day of the
 * week of the specified date 
 * @param d a date on the Gregorian Calendar
 * @return 0->Sunday, 1->Monday, 2->Tuesday, 3->Wednesday,
 * 4->Thursday, 5->Friday, 6->Saturday; otherwise, -1
 */
int getDayNum(const Date& d)
{
	string dayOfWeek = d.getDayOfWeek();
	
	if (dayOfWeek == "Sunday")
	    return 0;
	
	else if (dayOfWeek == "Monday")
	    return 1;
	
	else if (dayOfWeek == "Tuesday")
	    return 2;
	
	else if (dayOfWeek == "Wednesday")
	    return 3;
	    
	else if (dayOfWeek == "Thursday")
	    return 4;
	
	else if (dayOfWeek == "Friday")
	    return 5;
	
	else if (dayOfWeek == "Saturday")
	    return 6;
	
	else
        return -1; //Not a real day
}

int main(int argc, char* argv[]) 
{
    string usage = "DateOrganizer <data-file-name> <sort-code>\n";
    usage += "sort-code: -2 -month-day-year\n";
    usage += "           -1 -year-month-day\n";
    usage += "            0 +weekdayNumber+monthName+day+year\n";
    usage += "            1 +year+month+day\n";
    usage += "            2 +month+day+year";
    if (argc != 3)
    {
        cout << "Invalid number of command line arguments" << endl;
        cout << usage << endl;
        exit(1);
    }
    
    string filename = argv[1];
    int sortCode = stoi(argv[2]);
    PQueue<Date> dateQueue;
    
switch (sortCode)
{
    case -2: // -2 -month-day-year
    
    cout << "Dates from BundesHoliday.txt in -month-day-year Order" << endl;
    
    dateQueue = PQueue<Date>([](const Date& d1, const Date& d2)  
    {
        if (d1.getMonth() != d2.getMonth()) 
        {
            return d2.getMonth() - d1.getMonth();
                
        }
        
        else if (d2.getDay() != d1.getDay())
        {
            return d2.getDay() - d1.getDay();
        } 
        
        else 
        {
            return d2.getYear() - d1.getYear();
        }
    });
    
    break;
    
    case -1: // -1 -year-month-day
    
    cout << "Dates from BundesHoliday.txt in -year-month-day Order" << endl;
    
    dateQueue = PQueue<Date>([](const Date& d1, const Date& d2) 
    {
        if (d2.getYear() != d1.getYear()) 
        {
            return d2.getYear() - d1.getYear();
        }
        
        else if (d2.getMonth() != d1.getMonth())
        {
            return d2.getMonth() - d1.getMonth();
        } 
        
        else 
        {
            return d2.getDay() - d1.getDay();
        }
    });
        break;
    
    
    case 0:  // +weekdayNumber+monthName+day+year
    
    cout << "Dates from BundesHoliday.txt in +weekdayNumber+monthName+day+year Order" << endl;
    
    dateQueue = PQueue<Date>([](const Date& d1, const Date& d2) 
    {
        int dayNum1 = getDayNum(d1);
        int dayNum2 = getDayNum(d2);
        if (dayNum1 != dayNum2) 
        {
            return dayNum1 - dayNum2;
        }
        
        else if (d1.getMonth() != d2.getMonth())
        {
            return d1.getMonth() - d2.getMonth();
        } 
        
        else if (d1.getDay() != d2.getDay())
        {
            return d1.getDay() - d2.getDay();
        }
        
        else 
        {
            return d1.getYear() - d2.getYear();
        }
    });
        break;
    
    case 1: // 1 +year+month+day
    
    cout << "Dates from BundesHoliday.txt in +year+month+day Order" << endl;
    
    dateQueue = PQueue<Date>([](const Date& d1, const Date& d2) 
    {
        if (d1.getYear() != d2.getYear()) 
        {
            return d1.getYear() - d2.getYear();
        }
        
        else if (d1.getMonth() != d2.getMonth())
        {
            return d1.getMonth() - d2.getMonth();
        } 
        
        else 
        {
            return d1.getDay() - d2.getDay();
        }
    });
        break;
    
    case 2: // 2 +month+day+year
    
    cout << "Dates from BundesHoliday.txt in +month+day+year Order" << endl;
    
    dateQueue = PQueue<Date>([](const Date& d1, const Date& d2) 
    {
        if (d1.getMonth() != d2.getMonth()) 
        {
            return d1.getMonth() - d2.getMonth();
        }
        
        else if (d1.getDay() != d2.getDay())
        {
            return d1.getDay() - d2.getDay();
        } 
        
        else 
        {
            return d1.getYear() - d2.getYear();
        }
    });
        break;
    
    default:
        cout << "Invalid sort code" << endl;
        return 1;
}

ifstream txtFile("BundesHolidays.txt");
string line;

while (getline(txtFile, line)) {
        istringstream iss(line);
        int month, day, year;
        char delimiter;

        if (iss >> month >> delimiter >> day >> delimiter >> year)
        {
            Date date(month, day, year);
            dateQueue.insert(date);
        }
    }

    txtFile.close();

    while(!dateQueue.isEmpty())
    {
        Date date = dateQueue.remove();
        string monthName = date.getMonthName();
        cout<<date.getDayOfWeek()<<", "<<monthName<<" "<<date.getDay()<<", "<<date.getYear()<<endl;
    }

return 0;

}

