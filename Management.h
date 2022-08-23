/*
 *Tititle: COMP3140 Project Stage 1
 *File name: Management.h
 *File Type: Interface File 
 *Date: 11/13/2020
 */
#ifndef MANAGEMENT_DEF
#define MANAGEMENT_DEF
#include "Tenant.h"
#include "Manager.h"
#include <string>

using namespace std;

class Management
{ 
    protected:
        string fileName;
        double totalManager_Expense,totalRent,totalSalarayBonus_Expense;
        Tenant tenantArr[100];
        Manager managerArr[2];
    public:
        //Parameter constructor, takes in a file name as a string.
        Management(const string& newFileName);
        //Default constructor
        Management();
        //Destructor
        virtual ~Management();
        //Takes in an input file based on the fileName variable, scans through it and creates
        //tenantArr[] with any tenats and managerArr[] with any managers.
        void readFile();
        //Scans through tenantArr[] and checks their payment status, if it's true it checks their rental fee and adds it to a total
        //for the month as well as a total for 6 months. Does this process 6 times for each month.
        void collectRentalFee();
        //Scans through the tenantArr[] and lists any tenants, along with their current index, with payment status set to false.
        void listTenantsNotPay();
        //method to determine who hasn't paid their rent, then adds up the total missing rent for the month
        //then continues to add the total of missing rent for the past 6 months before printing it out.
        void missingRental();
        //Scans through the managerArr[] and grabs the total expenses data held in every manager then adds them together and displays the total. It continues to do this for every month
        //as well as the past 6 months.
        void totalExpense();
        //Scans through the managerArr[] and displays the total salary and bonus of every month as well as the total earned the past 6 months. It does this for every individual manager.
        void managerSalary_bouns();
        //The function that caculate the total Net income for each month and for six months.
        //NetIncome = (total rent collection)- (managers expense)-(salary and bonus expense)
        void netIncome();
        //Print out all tenants' profile.
        void profile_tenant();
        //Print out all Manager' profile.
        void profile_manager();
        //Mutators
        void setFileName(const string& newFileName);
        //Accessors
        string getFileName();
};
#endif