/*
 *Tititle: COMP3140 Project Stage 2
 *File name: Date.cpp
 *File Type: Implement File
 *Date: 11/20/2020
 */
#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

//Parameter Constructor
Date::Date(const int& newDay, const int& newMonth, const int& newYear)
: day (newDay), month (newMonth), year(newYear)
{
    if(!checkValidDate())
    {
        cout<<"Invalid Date"<<endl;
        day=1;
        month=1;
        year=1900;
    }
}

//Default Constructor
Date::Date()
: day (1), month (1), year(1900)
{
}

//copy constructor
Date::Date(const Date& date)
:day (date.getDay()), month (date.getMonth()), year(date.getYear())
{
   if(!checkValidDate())
    {
        cout<<"Invalid Date"<<endl;
        day=1;
        month=1;
        year=1;
    };
}

//Desctructor
Date::~Date()
{
}

//Mutator Functions
void Date::setDay(const int& newDay)
{
    if(!checkValidDate())
    {
        cout<<"Invalid Date"<<endl;
    }
    else
    {
        day = newDay;
    }
    
}
    
void Date::setMonth(const int& newMonth)
{
    if(!checkValidDate())
    {
        cout<<"Invalid Date"<<endl;
    }
    else
    {
        month = newMonth;
    }
}
    
void Date::setYear(const int& newYear)
{
    if(!checkValidDate())
    {
        cout<<"Invalid Date"<<endl;
    }
    else
    {
        year = newYear;
    }
}

//Accessor Function
int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
   return month;
}
    
int Date::getYear() const
{
    return year;
}

//returns a string with the date information
string Date::getDate() const
{
    return (to_string(day)+"-"+ convertMonth(month)+"-"+to_string(year));
}

//Converts a numbered month into a worded one. i.e. January, Febuary, March, April... etc
string Date :: convertMonth(int m) const
{
    string month_in_string;
    switch (m)
    {
        case 1:
        month_in_string = "January";
        break;

        case 2:
        month_in_string = "February";
        break;
        
        case 3:
        month_in_string = "March";
        break;
        
        case 4:
        month_in_string = "April";
        break;
        
        case 5:
        month_in_string = "May";
        break;
        
        case 6:
        month_in_string = "June";

        case 7:
        month_in_string = "July";
        break;

        case 8:
        month_in_string = "August";
        break;

        case 9:
        month_in_string = "September";
        break;

        case 10:
        month_in_string = "October";
        break;

        case 11:
        month_in_string = "November";
        break;

        case 12:
        month_in_string = "December";
        break;

        default:
        month_in_string = "No such Month.";
        break;
    }
    return month_in_string;
}

//Checks if the given numbers is a valid date by checking if days is between 
//1 - 31, Months is 1 - 12, and Year is correct.
bool Date::checkValidDate()
{
    if(day>=1 && day<=31 && month>=1 && month<=12 && year>0){
        return true;
    }
    else{
        return false;
    }
}