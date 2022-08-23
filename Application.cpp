/*
 *Tititle: COMP3140 Project Stage 3
 *File name: Application.cpp
 *File Type: Application File 
 *Date: 12/01/2020
 */
#include <iostream>
#include <string>
#include "Date.cpp"
#include "Person.cpp"
#include "Tenant.cpp"
#include "Manager.cpp"
#include "Management.cpp"
#include "NewManagement.cpp"
#include "FinalManagement.cpp"
#include <iomanip>

using namespace std;

//Display the application's title
void titleInfo();
//Display the Tenants profile
void TenantProfitInfo();
//Display the Managers profile
void ManagerProfitInfo();
//Display information of menu
void menuInfo();
//Function that import the File 
void importFile(FinalManagement* fnm_first,FinalManagement* fnm_second);
//search a tenants by name
void searchTenants(FinalManagement* fnm_first,FinalManagement* fnm_second);
//display Managers profile
void displayManagersProfile(FinalManagement* fnm_first,FinalManagement* fnm_second);
//modify Managers fields
void modifyManagersFields(FinalManagement* fnm_first,FinalManagement* fnm_second);
//Display the collected rental fees in total
void totalCollectedRentalFee(FinalManagement* fnm_first,FinalManagement* fnm_second);
//Display manager's total expense. 
void ManagerExpense(FinalManagement* fnm_first,FinalManagement* fnm_second);
//Display Tenants' total missing rent.
void tenantsMissingRent(FinalManagement* fnm_first,FinalManagement* fnm_second);
//Display the list of the names and house numbers of the tenants who did not pay their rental fees for 
//each month and its amount for the respective tenants and the total amount that they owe.
void listTenantsNotPay(FinalManagement* fnm_first,FinalManagement* fnm_second);
//Display both managers’ salaries and bonuses in total for each month and for a year.
void listManagerSalariesBonuses(FinalManagement* fnm_first,FinalManagement* fnm_second);
//Display the net income for each month and for a year.
void listNetIncome(FinalManagement* fnm_first,FinalManagement* fnm_second);
//Display financial statement for a year.
void displayFinancialStatement(FinalManagement* fnm_first,FinalManagement* fnm_second);

//main function
int main()
{
   titleInfo();
   FinalManagement fnm_first;
   FinalManagement fnm_second;
   FinalManagement* f1 = &fnm_first;
   FinalManagement* f2 = &fnm_second;
   importFile(f1,f2);
   fnm_first.setMonth_Name();
   fnm_second.setMonth_Name();
   char userEnter='0';
   //Menu
   while(userEnter!='q')
   {
      menuInfo();
      cin>>userEnter;
      switch (userEnter)
      {
         case '1':
         searchTenants(f1,f2);     
         break;
         case '2':
         displayManagersProfile(f1,f2);
         modifyManagersFields(f1,f2);
         break;
         case '3':
         totalCollectedRentalFee(f1,f2);
         break;
         case '4':
         ManagerExpense(f1,f2);
         break;
         case '5':
         tenantsMissingRent(f1,f2);
         break;
         case '6':
         listTenantsNotPay(f1,f2);
         break;
         case '7':
         listManagerSalariesBonuses(f1,f2);
         break;
         case '8':
         listNetIncome(f1,f2);
         break;
         case '9':
         displayFinancialStatement(f1,f2);
         break;
         default:
         break;
      }        
   }
   cout<<"**********************************************************************"<<endl;
   cout<<"******THANK YOU FOR USING RENTAL PROPERTY MANAGEMENT APPLICATION******"<<endl;
   cout<<"*********************************BYE!*********************************"<<endl;
   return 0; 
}

//Display financial statement for a year.
void displayFinancialStatement(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   double* arr1 = fnm_first->financialStatement();
   double* arr2 = fnm_second->financialStatement();
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"Financial Statement For A Year:"<<endl;
   for(int index=0;index<5;index++)
   {
      if(index==0)
      {
         double totalRevenu = *(arr1+index) +*(arr2+index);
         cout<<"Total Revenu"<<"\t\t"<<"$"<<fixed<<setprecision(2)<<totalRevenu<<endl;
      }
      else if(index==1)
      {
         double temp_totalExpense = *(arr1+index) +*(arr2+index);
         cout<<"Total Expense"<<"\t\t"<<"$"<<fixed<<setprecision(2)<<temp_totalExpense<<endl;
      }
      else if(index==2)
      {
         cout<<"Earning Before Tax"<<"\t"<<"$"<<fixed<<setprecision(2)<<arr1[index]+arr2[index]<<endl;
      }
      else if(index==3)
      {
         cout<<"Tax(%12)"<<"\t\t"<<"$"<<fixed<<setprecision(2)<<arr1[index]+arr2[index]<<endl;
      }
      else if(index==4)
      {
         cout<<"Earning After Tax"<<"\t"<<"$"<<fixed<<setprecision(2)<<arr1[index]+arr2[index]<<endl;
      }
   }
   cout<<"----------------------------------------------------------------------"<<endl;
}

//Display the net income for each month and for a year.
void listNetIncome(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"Net Income For Each Month:"<<endl;
   fnm_first->netIncome();
   fnm_second->netIncome();
   double totalNetIncome_oneYear = fnm_first->getTotalIncome() + fnm_second->getTotalIncome();
   cout<<"*Total Net Income For A Year: $"<<totalNetIncome_oneYear<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;  
}

//Display both managers’ salaries and bonuses in total for each month and for a year.
void listManagerSalariesBonuses(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"Both Managers' Salaries And Bonuses In Total For Each Month:"<<endl;
   fnm_first->managerSalary_bouns();
   fnm_second->managerSalary_bouns();
   double totalSalaryBouns_oneYear = fnm_first->getTotalSalarayBonus()+fnm_second->getTotalSalarayBonus();
   cout<<"*Total Managers' Salaries And Bonuses For A Year: $"<<totalSalaryBouns_oneYear<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
}

//Display the list of the names and house numbers of the tenants who did not pay their rental fees for 
//each month and its amount for the respective tenants and the total amount that they owe.
void listTenantsNotPay(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"The list of the tenants who did not pay their rental fees:"<<endl;
   fnm_first->listTenantsNotPay();
   fnm_second->listTenantsNotPay();
   cout<<"----------------------------------------------------------------------"<<endl;
}

//Display Tenants' total missing rent.
void tenantsMissingRent(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"The Total Amount Of Missing Rental Fees For Each Month:"<<endl;
   fnm_first->missingRental();
   fnm_second->missingRental();
   double totalMissingRent_oneYear = fnm_first->getTotalMissRent()+fnm_second->getTotalMissRent();
   cout<<"*Total Missing Rental Fees For A Year: $"<<totalMissingRent_oneYear<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
}

//Display manager's total expense. 
void ManagerExpense(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"Total Expense For Each Month:"<<endl;
   fnm_first->totalExpense();
   fnm_second->totalExpense();
   double totalExpense_oneYear = fnm_first->getTotalExpense()+fnm_second->getTotalExpense();
   cout<<"*Total Expense For A Year: $"<<totalExpense_oneYear<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
}

//Display the collected rental fees in total
void totalCollectedRentalFee(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"The Total Collected Rental Fees For Each Month:"<<endl;
   fnm_first->collectRentalFee();
   fnm_second->collectRentalFee();
   double totalRentalFee_oneYear = fnm_first->getTotalRent()+fnm_second->getTotalRent();
   cout<<"*The Collected Rental Fees In Total For A Year: $"<<totalRentalFee_oneYear<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
}

//modify Managers fields
void modifyManagersFields(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   char userEnter;
   int ManagerChoose,changefield_option,first_or_second_month,
       firstManagerFile =1,secondManagerFile=2;
   string changeManager_content, managerName;
   cout<<"Would You Like to Modify this Manager's fields?(Y/N):"<<endl;
   cin>>userEnter; 
   while(userEnter!='Y' && userEnter!='N')//if user enter invalid inputs
   {
      cout<<"***Invalid Input***"<<endl;
      cout<<"Would You Like to Modify this Manager's fields?(Y/N):"<<endl;
      cin>>userEnter;
      //clear cin buffer
      cin.clear();
      cin.sync();
   }
   if(userEnter=='Y')
   {
      cout<<"Which Managers Would You Like to Modify?"<<endl;
      cout<<"Enter 1 or 2:"<<endl;
      cin>>ManagerChoose;
      while(ManagerChoose!=1 && ManagerChoose!=2)
      {
         cout<<"The Manager Does Not Exist."<<endl;
         cout<<"Enter 1 or 2:"<<endl;
         cin>>ManagerChoose;
         cin.clear();
         cin.sync();
      }
      ManagerChoose--;   
      managerName = fnm_first->getManagerName(ManagerChoose);
      bool modify_ManagerProfit1=false,modify_ManagerProfit2=false,check_modifySalarayBonus1=false,check_modifySalarayBonus2=false;
      while(userEnter=='Y')
      {
         ManagerProfitInfo();//display manager fields option
         cin>>changefield_option; 
         while(changefield_option<1 && changefield_option>6)//if user enter invalid inputs
         {
            cout<<"***No Such That Option***"<<endl;
            cout<<"Enter 1 - 6:"<<endl;
            cin>>changefield_option;
            cin.clear();
            cin.sync();
         }
         switch (changefield_option)
         {
            case 1://Change the manager's name in both file
               cout<<"Enter "<<managerName<<"'s New Name:"<<endl;
               cin.clear();
               cin.sync();
               getline(cin,changeManager_content);
               modify_ManagerProfit1 = fnm_first->changeManagerField(ManagerChoose,changefield_option,changeManager_content,firstManagerFile);
               modify_ManagerProfit2 = fnm_second->changeManagerField(ManagerChoose,changefield_option,changeManager_content,secondManagerFile);
            break;
            case 2://Change the manager's age in both file
               cout<<"Enter "<<managerName<<"'s New Age:"<<endl;
               cin>>changeManager_content;
               modify_ManagerProfit1 = fnm_first->changeManagerField(ManagerChoose,changefield_option,changeManager_content,firstManagerFile);
               modify_ManagerProfit2 = fnm_second->changeManagerField(ManagerChoose,changefield_option,changeManager_content,secondManagerFile);
            break;
            case 3://Change the manager's gender in both file
               cout<<"Enter "<<managerName<<"'s New Gender:"<<endl;
               cin>>changeManager_content;
               modify_ManagerProfit1 = fnm_first->changeManagerField(ManagerChoose,changefield_option,changeManager_content,firstManagerFile);
               modify_ManagerProfit2 = fnm_second->changeManagerField(ManagerChoose,changefield_option,changeManager_content,secondManagerFile);
            break;
            case 4://Change the manager's hired day in both file
               cout<<"Enter "<<managerName<<"'s New Hired Day(Eg: Month/Day/Year):"<<endl;
               cin>>changeManager_content;
               modify_ManagerProfit1 = fnm_first->changeManagerField(ManagerChoose,changefield_option,changeManager_content,firstManagerFile);
               modify_ManagerProfit2 = fnm_second->changeManagerField(ManagerChoose,changefield_option,changeManager_content,secondManagerFile);
            break;
            default:
               break;
         }
         if(changefield_option==5)//Change the manager's salary in both file
         {
            cout<<"Enter 1 For First Six Month."<<endl;
            cout<<"Enter 2 For Second Six Month."<<endl;
            cin>>first_or_second_month;
            cin.clear();
            cin.sync();
            while(first_or_second_month!=1 && first_or_second_month!=2)//Invalid input
            {
               cout<<"The Month Does Not Exist."<<endl;
               cout<<"Enter 1 or 2:"<<endl;
               cin>>first_or_second_month;
               cin.clear();
               cin.sync();
            }
            cout<<"Enter "<<managerName<<"'s New Salary:"<<endl;
            cin>>changeManager_content;
            if(first_or_second_month==1)//change first six month
            {
               check_modifySalarayBonus1 = fnm_first->changeManagerSalaryBonus(ManagerChoose,changefield_option,changeManager_content,firstManagerFile); 
            }
            else//change second six month
            {
               check_modifySalarayBonus2 = fnm_second->changeManagerSalaryBonus(ManagerChoose,changefield_option,changeManager_content,secondManagerFile);
            }
            
         }
         else if(changefield_option==6)//Change the manager's bonus in both file
         {
            cout<<"First Six Month Or Second Six Month?"<<endl;
            cin>>first_or_second_month;
            //clear cin buffer
            cin.clear();
            cin.sync();
            //Invalid input
            while(first_or_second_month!=1 && first_or_second_month!=2)
            {
               cout<<"The Month Does Not Exist."<<endl;
               cout<<"Enter 1 or 2:"<<endl;
               cin>>first_or_second_month;
               //clear cin buffer
               cin.clear();
               cin.sync();
            }
            cout<<"Enter "<<managerName<<"'s New Bonus:"<<endl;
            cin>>changeManager_content;
            if(first_or_second_month==1)//change first six month
            {
               check_modifySalarayBonus1 = fnm_first->changeManagerSalaryBonus(ManagerChoose,changefield_option,changeManager_content,firstManagerFile); 
            }
            else//change SECOND six month
            {
               check_modifySalarayBonus2 = fnm_second->changeManagerSalaryBonus(ManagerChoose,changefield_option,changeManager_content,secondManagerFile);
            }
         }
         //clear cin buffer
         cin.clear();
         cin.sync();
         cout<<"***Change Successful!***"<<endl;
         cout<<"Would you like to change another field?(Y/N):"<<endl;
         cin>>userEnter;
         while(userEnter!='Y' && userEnter!='N')//if user enter invalid inputs
         {
            cout<<"***Invalid Input***"<<endl;
            cout<<"Would you like to change another field?(Y/N):"<<endl;
            cin>>userEnter;
            //clear cin buffer
            cin.clear();
            cin.sync();
         }
      }
   }             
}

//display Managers profile
void displayManagersProfile(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"First Six Month:"<<endl;
   fnm_first->profile_manager(); 
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"Second Six Month:"<<endl;
   fnm_second->profile_manager();
   cout<<"----------------------------------------------------------------------"<<endl;
}

//search a tenants by name
void searchTenants(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   //clear cin buffer
   cin.clear();
   cin.sync();
   string enterName="";
   char userEnter;
   cout<<"Enter The Tenant's Name(Case-Sensitive):"<<endl;
   getline(cin,enterName);
   int indexTenant = fnm_first->searchTenant(enterName);
   while(indexTenant == -1)//Tenants can not be found
   {
      cout<<"The Tenant Does Not Exist. Please Enter Tenant's Name Again: "<<endl;
      getline(cin,enterName);
      indexTenant = fnm_first->searchTenant(enterName);
      //clear cin buffer
      cin.clear();
      cin.sync();
   }
   cout<<endl;
   //modify the Tenants filed
   cout<<"Would You Like to Modify this Tenant's fields?(Y/N):"<<endl;
   cin>>userEnter;
   while(userEnter!='Y' && userEnter!='N')//Invalid Input
   {
      cout<<"***Invalid Input***"<<endl;
      cout<<"Would You Like to Modify this Tenant's fields?(Y/N):"<<endl;
      cin>>userEnter;
      //clear cin buffer
      cin.clear();
      cin.sync();
   } 
   while(userEnter=='Y')
   {
      int firstTenantFile =1,secondTenantFile=2;
      bool modify_TenantProfit1=false,modify_TenantProfit2=false;
      //When both file has been modify,jump out the loop
      while(modify_TenantProfit1 == false || modify_TenantProfit2 == false)
      {
            string changeTenant_content;
            int changefield_option;
            TenantProfitInfo();
            cin>>changefield_option;
            switch (changefield_option)
            {
               case 1://Change the tenants's name in both file
                  cout<<"Enter "<<enterName<<"'s New Name:"<<endl;
                  cin.clear();
                  cin.sync();
                  getline(cin,changeTenant_content);
                  modify_TenantProfit1 = fnm_first->changeTenantField(indexTenant,changefield_option,changeTenant_content,firstTenantFile);
                  modify_TenantProfit2 = fnm_second->changeTenantField(indexTenant,changefield_option,changeTenant_content,secondTenantFile);
               break;
               case 2://Change the tenants's age in both age
                  cout<<"Enter "<<enterName<<"'s New Age:"<<endl;
                  cin>>changeTenant_content;
                  modify_TenantProfit1 = fnm_first->changeTenantField(indexTenant,changefield_option,changeTenant_content,firstTenantFile);
                  modify_TenantProfit2 = fnm_second->changeTenantField(indexTenant,changefield_option,changeTenant_content,secondTenantFile);
               break;
               case 3://Change the tenants's gender in both file
                  cout<<"Enter "<<enterName<<"'s New Gender:"<<endl;
                  cin>>changeTenant_content;
                  modify_TenantProfit1 = fnm_first->changeTenantField(indexTenant,changefield_option,changeTenant_content,firstTenantFile);
                  modify_TenantProfit2 = fnm_second->changeTenantField(indexTenant,changefield_option,changeTenant_content,secondTenantFile);
               break;
               case 4://Change the tenants's job in both file
                  cout<<"Enter "<<enterName<<"'s New Job:"<<endl;
                  cin.clear();
                  cin.sync();
                  getline(cin,changeTenant_content);
                  modify_TenantProfit1 = fnm_first->changeTenantField(indexTenant,changefield_option,changeTenant_content,firstTenantFile);
                  modify_TenantProfit2 = fnm_second->changeTenantField(indexTenant,changefield_option,changeTenant_content,secondTenantFile);
               break;
               case 5://Change the tenants's unit# in both file
                  cout<<"Enter "<<enterName<<"'s New Unit#:"<<endl;
                  cin>>changeTenant_content;
                  modify_TenantProfit1 = fnm_first->changeTenantField(indexTenant,changefield_option,changeTenant_content,firstTenantFile);
                  modify_TenantProfit2 = fnm_second->changeTenantField(indexTenant,changefield_option,changeTenant_content,secondTenantFile);
               break;
               case 6://Change the tenants's moving day in both file
                  cout<<"Enter "<<enterName<<"'s New Moving Day(Eg: Month/Day/Year):"<<endl;
                  cin>>changeTenant_content;
                  modify_TenantProfit1 = fnm_first->changeTenantField(indexTenant,changefield_option,changeTenant_content,firstTenantFile);
                  modify_TenantProfit2 = fnm_second->changeTenantField(indexTenant,changefield_option,changeTenant_content,secondTenantFile);
               break;
               case 7://Change the tenants's monthly rent in both file
                  cout<<"Enter "<<enterName<<"'s New Monthly Rent:"<<endl;
                  cin>>changeTenant_content;
                  modify_TenantProfit1 = fnm_first->changeTenantField(indexTenant,changefield_option,changeTenant_content,firstTenantFile);
                  modify_TenantProfit2 = fnm_second->changeTenantField(indexTenant,changefield_option,changeTenant_content,secondTenantFile);
               break; 
               default:
                  break;
            }
            //clear cin buffer
            cin.clear();
            cin.sync();
            if(modify_TenantProfit1 == false || modify_TenantProfit2 == false)
            {
               cout<<"Invalid Value, Please Enter Again:"<<endl;
            }
      }
      cout<<"***Change Successful!***"<<endl;
      cout<<"Would you like to change another field?(Y/N):"<<endl;
      cin>>userEnter;
      while(userEnter!='Y' && userEnter!='N')
      {
         cout<<"***Invalid Input***"<<endl;
         cout<<"Would you like to change another field?(Y/N):"<<endl;
         cin>>userEnter;
         //clear cin buffer
         cin.clear();
         cin.sync();
      } 
   }  
}

//Function that import the File 
void importFile(FinalManagement* fnm_first,FinalManagement* fnm_second)
{
   //Variables for holding each file's name
   string tenantFile1,managerFile1,tenantFile2,managerFile2;
   //Reading the first Tenants File
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<"Enter Your First Tenants File Name(Eg.Tenants.csv): "<<endl;
   cin>>tenantFile1;
   fnm_first->setTenantFileName(tenantFile1);
   //Check Whether File name is valid
   while(!fnm_first->reading_TenantFile())
   {
      cout<<"Invalid Tenants File Name. Please Enter Again:"<<endl;
      cin>>tenantFile1;
      fnm_first->setTenantFileName(tenantFile1);
   }
   cout<<"***Successful!***"<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<endl;
   //Reading the first Managers File
   cout<<"Enter Your First Managers File Name(Eg.Managers.csv): "<<endl;
   cin>>managerFile1;
   fnm_first->setManagerFileName(managerFile1);
   //Check Whether File name is valid
   while(!fnm_first->reading_ManagerFile())
   {
      cout<<"Invalid Manager File Name. Please Enter Again:"<<endl;
      cin>>managerFile1;
      fnm_first->setManagerFileName(managerFile1);
   }
   cout<<"***Successful!***"<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<endl;
   //clear cin buffer
   cin.clear();
   cin.sync();
   //Reading the second Tenants File
   cout<<"Enter Your Second Tenants File Name(Eg.Tenants2.csv): "<<endl;
   cin>>tenantFile2;
   fnm_second->setTenantFileName(tenantFile2);
   //Check Whether File name is valid
   while(!fnm_second->reading_TenantFile())
   {
      cout<<"Invalid Tenants File Name. Please Enter Again:"<<endl;
      cin>>tenantFile2;
      fnm_second->setTenantFileName(tenantFile2);
   }
   cout<<"***Successful!***"<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<endl;
   //Reading the second Managers File
   cout<<"Enter Your Second Managers File Name(Eg.Managers2.csv): "<<endl;
   cin>>managerFile2;
   fnm_second->setManagerFileName(managerFile2);
   //Check Whether File name is valid
   while(!fnm_second->reading_ManagerFile())
   {
      cout<<"Invalid Manager File Name. Please Enter Again:"<<endl;
      cin>>managerFile2;
      fnm_second->setManagerFileName(managerFile2);
   }
   cout<<"***Successful!***"<<endl;
   cout<<"----------------------------------------------------------------------"<<endl;
   cout<<endl;
}

//Display the Managers profile
void ManagerProfitInfo()
{
   cout<<"Which Field Would You Like To Modify?"<<endl;
   cout<<"1. Manager's Name."<<endl;
   cout<<"2. Manager's Age."<<endl;
   cout<<"3. Manager's Gender."<<endl;
   cout<<"4. Manager's Hired Date."<<endl;
   cout<<"5. Manager's Salary."<<endl;
   cout<<"6. Manager's Bonus."<<endl;
}

//Display the Tenants profile
void TenantProfitInfo()
{
   cout<<"Which Field Would You Like To Modify?"<<endl;
   cout<<"1. Tenant's Name."<<endl;
   cout<<"2. Tenant's Age."<<endl;
   cout<<"3. Tenant's Gender."<<endl;
   cout<<"4. Tenant's Job."<<endl;
   cout<<"5. Tenant's Unit#."<<endl;
   cout<<"6. Tenant's Moving Day."<<endl;
   cout<<"7. Tenant's Monthly Rent."<<endl;
}

//Display the application's title
void titleInfo()
{
   cout<<endl;
   cout<<"**********************************************************************"<<endl;
   cout<<"***************RENTAL PROPERTY MANAGEMENT APPLICATION*****************"<<endl;
   cout<<"**********************************************************************"<<endl;
   cout<<endl;
}

//Display information of menu
void menuInfo()
{
   cout<<"**********************************************MENU*******************************************************"<<endl;
   cout<<"1. Search For A Tenant's Profit By Name."<<endl;
   cout<<"2. Display For All Managers' Profit."<<endl;
   cout<<"3. Display The Collected Rental Fees In Total For Each Month And For A Year."<<endl;
   cout<<"4. Display Total Expense For Each Month And For A Year."<<endl;
   cout<<"5. Display The Amount Of Missing Rental Fees In Total For Each Month And For A Year."<<endl;
   cout<<"6. Display The Tenants Who did Not Pay Their Rental Fees For Each Month"<<endl;
   cout<<"7. Display both managers' salaries and bonuses in total for each month and for a year."<<endl;
   cout<<"8. Display The Net Income For Each Month And For A Year."<<endl;
   cout<<"9. Display The Summary Of The Financial Statement For A Year: Total Revenue (Total Rental Fees), Total"<<endl; 
   cout<<"   Expense, Earning Before Tax, Tax (12%), And Earning After Tax."<<endl;
   cout<<"Enter q For Quit."<<endl;
   cout<<"********************************************************************************************************"<<endl;
}
