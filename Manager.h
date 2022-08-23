/*
 *Tititle: COMP3140 Project Stage 1
 *File name: Manager.h
 *File Type: Interface File 
 *Date: 11/13/2020
 */
#ifndef MANAGER_H
#define MANAGER_H
#include <string>
#include"Date.h"
#include"Person.h"

using namespace std;

class Manager : public Person
{
    private:
        Date hired_date;
        double salary;
        double bouns;
        double monthly_expense[6];
    public:
        //Parameter Constructor
        Manager(const string& newName,const int& newAge,
        const string& newGender,const Date& newHired_date,
        const double& newSalary,const double& newBouns,
        double newMonthly_expense[6]);
        //Default Constructor
        Manager();
        //Destructors
        virtual ~Manager();
        //Mutators
        void setHired_Date(const Date& date);
        void setSalary(const double& newSalary);
        void setBouns(const double& newBouns);
        void setMonthly_expense(double newMonthly_expense[6]);
        //Accessors
        Date getHired_Date() const;
        double getSalary() const;
        double getBouns() const;
        double* getMonthly_expense();
        //Overridden printInfo() function from base class
        virtual void printInfo() const;
};
#endif

