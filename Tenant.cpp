/*
 *Tititle: COMP3140 Project Stage 2
 *File name: Tenant.cpp
 *File Type: Implement File 
 *Date: 11/20/2020
 */
#include <string>
#include <iostream>
#include "Tenant.h"

using namespace std;

//Parameter Constructor
Tenant::Tenant(const string& newName,const int& newAge, 
                const string& newGender,const string& newJob, 
                const int& newUnitNumber, Date newMoveIn_Day,
                const double& newMonthly_rent, char newPayment_status[6])
:Person(newName,newAge,newGender),job(newJob),unitNumber(newUnitNumber),
movingIn_Date(newMoveIn_Day),monthly_rent(newMonthly_rent)
{
    for(int index=0;index<6;index++)
    {
        payment_status[index] = newPayment_status[index];
    }
}

//Default Comstructor
Tenant::Tenant()
:Person("",0,""),job(""),unitNumber(0),monthly_rent(0.0)
{
    
}

Tenant::~Tenant()
{

}

//Mutators
void Tenant::setJob(const string& newJob)
{
    job = newJob;
}

void Tenant::setUnitNumber(const int& newUnitNumber)
{
    unitNumber = newUnitNumber;
}

void Tenant::setMovingIn_Date(const Date& date)
{
    movingIn_Date = date;
}

void Tenant::setMonthlyRent(const double& newMonthly_rent)
{
    monthly_rent = newMonthly_rent;
}

void Tenant::setPaymentStatus(char newPayment_status[6])
{
    for(int index=0;index<6;index++)
    {
        payment_status[index] = newPayment_status[index];
    }
}

//Accessors
string Tenant::getJob() const
{
    return job;
}

int Tenant::getUnitNumber() const
{
    return unitNumber;
} 

Date Tenant::getmovingIn_Date() const
{
    return movingIn_Date;
}

double Tenant::getMonthlyRent() const
{
    return monthly_rent;
}

char* Tenant::getPaymentStatus()
{
    return payment_status;
}

//Overridden printInfo() function from base class
void Tenant::printInfo() const
{
    Person::printInfo();
    cout<<"Job: "<<job<<endl;
    cout<<"Unit#: "<<unitNumber<<endl;
    cout<<"Moving In Date: "<<movingIn_Date.getDate()<<endl;
    cout<<"Monthly Rent: "<<monthly_rent<<endl;
}