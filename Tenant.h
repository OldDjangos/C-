/*
 *Tititle: COMP3140 Project Stage 1
 *File name: Tenant.h
 *File Type: Interface File 
 *Date: 11/13/2020
 */
#ifndef TENANT_H
#define TENANT_H
#include <string>
#include"Date.h"
#include"Person.h"

using namespace std;

class Tenant : public Person
{
    private:
        string job;
        int unitNumber;
        Date movingIn_Date;
        double monthly_rent;
        char payment_status[6];
    public:
        //Parameter Constructor
        Tenant(const string& newName,const int& newAge, 
                const string& newGender,const string& newJob, 
                const int& newUnitNumber, Date newMoveIn_Day,
                const double& newMonthly_rent, char newPayment_status[6]);
        //Default Constructor
        Tenant();
        //Destructors
        virtual ~Tenant();
        //Mutators
        void setJob(const string& newJob);
        void setMovingIn_Date(const Date& date);
        void setUnitNumber(const int& newUnitNumber);
        void setMonthlyRent(const double& newMonthly_rent);
        void setPaymentStatus(char newPayment_status[6]);
        //Accessors
        string getJob() const; 
        int getUnitNumber() const; 
        Date getmovingIn_Date() const; 
        double getMonthlyRent() const;
        char* getPaymentStatus();
        //Overridden printInfo() function from base class
        virtual void printInfo() const;
};
#endif