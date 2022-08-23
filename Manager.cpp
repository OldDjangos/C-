/*
 *Tititle: COMP3140 Project Stage 2
 *File name: Manager.cpp
 *File Type: Implement File 
 *Date: 11/20/2020
 */
#include <string>
#include <iostream>
#include "Person.h"
#include "Manager.h"

using namespace std;

//Parameter Constructor
Manager::Manager(const string& newName,const int& newAge,
        const string& newGender,const Date& newHired_date,
        const double& newSalary,const double& newBouns,
       double newMonthly_expense[6])
:Person(newName,newAge,newGender),hired_date(newHired_date),salary(newSalary),bouns(newBouns)
{
        for(int index=0;index<6;index++)
        {
                monthly_expense[index] = newMonthly_expense[index];
        }
}

//Default Constructor
Manager::Manager()
:Person("",0,""),hired_date(),salary(0.0),bouns(0.0)
{

}

//Destructor
Manager::~Manager()
{
    
}

//Mutators
void Manager::setHired_Date(const Date& date)
{
        hired_date=date;
}
void Manager::setSalary(const double& newSalary)
{
        salary=newSalary;
}

void Manager::setBouns(const double& newBouns)
{
        bouns=newBouns;
}
void Manager::setMonthly_expense(double newMonthly_expense[6])
{
        for(int index=0;index<6;index++)
        {
                monthly_expense[index] = newMonthly_expense[index];
        }
}

//Accessors
Date Manager::getHired_Date() const
{
        return hired_date;
}
double Manager::getSalary() const
{
        return salary;
}

double Manager::getBouns() const
{
        return bouns;
}

double* Manager::getMonthly_expense() 
{
        return monthly_expense;
}

//Overridden printInfo() function from base class
void Manager::printInfo() const
{
        Person::printInfo();
        cout<<"Hired date: "<< hired_date.getDate()<<endl;
        cout<<"Salary: "<< salary<<endl;
        cout<<"Bouns: "<< bouns<<endl;
}