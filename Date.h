/*
 *Tititle: COMP3140 Project Stage 1
 *File name: date.h
 *File Type: Interface File 
 *Date: 11/13/2020
 */
#ifndef DATE_H
#define DATE_H
#include <string>

using namespace std;

class Date
{
      private:
            int day, month, year;
            //Converts a numbered month into a worded one. i.e. January, Febuary, March, April... etc
            string convertMonth(int m) const;
            //Checks if the given numbers is a valid date by checking if days is between 
            //1 - 31, Months is 1 - 12, and Year is correct.
            bool checkValidDate();
      public:
            //Parameter Constructor
            Date(const int& newDay, const int& newMonth, const int& newYear);
            //Default Constructor
            Date();
            //Copy Constructor
            Date(const Date& date);
            //Destructors
            ~Date();
            //Mutators 
            void setDay(const int& newDay);
            void setMonth(const int& newMonth);
            void setYear(const int& newYear);
            //Accessors
            int getDay() const;
            int getMonth() const;
            int getYear() const;
            //Return full date information
            string getDate() const; 
};
#endif