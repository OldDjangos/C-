/*
 *Tititle: COMP3140 Project Stage 3
 *File name: FinalManagement.h
 *File Type: Interface File 
 *Date: 12/01/2020
 */
#ifndef FINALMANAGEMENT_DEF
#define FINALMANAGEMENT_DEF
#include "Management.h"
#include "NewManagement.h"
#include "Tenant.h"
#include "Manager.h"
#include <string>

class FinalManagement:public NewManagement
{
    private:
        const int MAX_TENANT=100;
        const int MAX_MANAGER=2;
        //static vector for saving the index of tenants who did not pay the rent 
        static vector<int> notPay_tenants_index;
        //static vector for saving the accumulated rental fee that a tenant owe
        static vector<double> accumulate_Amount;
        //static int variable for counting the time that listTenantsNotPay() have been called
        static int listNotPayFunction_callTimes;
        //static int variable for counting the time that financialStatement() have been called
        int financialStatement_callTimes;
        //Array to hold each financial statement
        double financial_arr[5];
        //Funtion for display a signle profile of a tenants
        void displaySingleTenantProfit(const int& tenantIndex);
        //Check the notPay_tenants_index vector whether contain the current index of tenants
        int checkExist_NotPayTentants(const int& tenants_index);
        //Display the accumulated rental fee that a tenant owe
        void displayTotalRentTenantsOwe(const int& tenants_index);
        //Function for modifying the orignal manager csv file
        void changeManagerOrignalFile(int changeRow,int changeColumn,string changeContent,int check);
        //Function for modifying the orignal tenant csv file
        void changeTenantOrignalFile(int changeRow,int changeColumn,string changeContent,int check);
    public:
        //Parameter Constructor
        FinalManagement(const string& newTenant_FileName,const string& newManager_FileName);
        //Default Constructor
        FinalManagement();
        //Destructor
        virtual ~FinalManagement();
        //Function for searching a tenant by his/her name
        int searchTenant(const string& enterName);
        //Function for changing the tenants' field and save all changes to the original csv files
        bool changeTenantField(const int& index_arr,const int& changeOption,string content,int check);
        //Function for changing the managers' field and save all changes to the original csv files
        bool changeManagerField(const int& index_arr,const int& changeOption,string content,int check);
        //Function for reading the tenant's csv file
        bool reading_TenantFile();
        //Function for reading the manager's csv file
        bool reading_ManagerFile();
        //Function that returns the Manager's name
        string getManagerName(const int& index_arr);
        //Function for changing the managers' salary and bonus, it will save all changes to the original csv files
        bool changeManagerSalaryBonus(const int& index_arr,const int& changeOption,string content,int check);
        //Display the summary of the financial statement for a year: total revenue (total rental fees), 
        //total expense, earning before tax, tax (12%), and earning after tax
        double* financialStatement();
        //Overridden collectRentalFee function
        virtual void collectRentalFee();
        //Overridden totalExpense function
        virtual void totalExpense();
        //Overridden missingRental function
        virtual void missingRental();
        //Overridden listTenantsNotPay function
        virtual void listTenantsNotPay();
        //overridden managerSalary_bouns function
        virtual void managerSalary_bouns();
        //Overridden netIncome function
        virtual void netIncome();
        //Accessors
        double getTotalRent() const;
        double getTotalExpense() const;
        double getTotalMissRent() const;
        double getTotalSalarayBonus() const;
        double getTotalIncome() const;     
};
#endif