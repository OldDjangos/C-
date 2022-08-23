/*
 *Tititle: COMP3140 Project Stage 2
 *File name: NewManagement.h
 *File Type: Interface File 
 *Date: 11/20/2020
 */
#ifndef NEWMANAGEMENT_DEF
#define NEWMANAGEMENT_DEF
#include "Management.h"
#include "Tenant.h"
#include "Manager.h"
#include <string>

class NewManagement:public Management
{
    protected:
        string tenantFileName, managerFileName;
        string month_name[6];
        double total_missRent,totalIncome;
        //Check the tenant's payment status
        bool checkPaymentStatus(char payment_state);
    public:
        //Parameter Constructor
        NewManagement(const string& newTenant_FileName,const string& newManagerFileName);
        //Default Constructor
        NewManagement();
        //Destructor
        virtual ~NewManagement();
        //Takes in an input file based on the tenantFileName variable, scans through it and 
        //put data into tenantArr[100] with any tenats.
        void readTenantFile();
        //Takes in an input file based on the managerFileName variable, scans through it and 
        //put data into managerArr[2] with any tenats.
        void readManagerFile();
        //Scans through tenantArr[100] and checks their payment status, if it's true it checks their rental fee and adds it to a total
        //for the month as well as a total for 6 months. Does this process 6 times for each month.
        virtual void collectRentalFee();
        //Scans through the tenantArr[100] and lists any tenants, along with their current index, with payment status set to false(Not Pay).
        virtual void listTenantsNotPay();
        //This function to determine who hasn't paid their rent, then adds up the total missing rent for the month
        //then continues to add the total of missing rent for the past 6 months before printing it out.
        virtual void missingRental();
        //Scans through the managerArr[100] and grabs the total expenses data held in every manager then adds them together and displays the total. 
        //It continues to do this for every month as well as the past 6 months.
        virtual void totalExpense();
        //Scans through the managerArr[100] and displays the total salary and bonus of every month as well as 6 months. 
        //It does this for every individual manager.
        virtual void managerSalary_bouns();
        //The function that caculate the total Net income for each month and for six months.
        //NetIncome = (total rent collection)- (managers expense)-(salary and bonus expense)
        virtual void netIncome();
        //Set current six month's name from file
        void setMonth_Name();
        //Mutators
        void setTenantFileName(const string& newTenant_FileName);
        void setManagerFileName(const string& newManager_FileName);
        //Accessors
        string getTenantFileName();
        string getManagerFileName();


};
#endif
