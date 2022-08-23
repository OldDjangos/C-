/*
 *Tititle: COMP3140 Project Stage 3
 *File name: FinalManagement.cpp
 *File Type: Implement File 
 *Date: 12/01/2020
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "FinalManagement.h"
#include "Tenant.h"
#include "Manager.h"
#include <bits/stdc++.h>

using namespace std;

//Implementing the static variable and vector
vector<int> FinalManagement::notPay_tenants_index;
vector<double> FinalManagement::accumulate_Amount;
int FinalManagement::listNotPayFunction_callTimes=0;

//Parameter Constructor
FinalManagement::FinalManagement(const string& newTenant_FileName,const string& newManager_FileName)
:NewManagement(newTenant_FileName,newManager_FileName),financialStatement_callTimes(0)
{
    for(int x=0;x<5;x++)
    {
        financial_arr[x] = 0.0;
    }
}

//Default Constructor
FinalManagement::FinalManagement()
:NewManagement(),financialStatement_callTimes(0)
{
    for(int x=0;x<5;x++)
    {
        financial_arr[x] = 0.0;
    }
}

//Destructor
FinalManagement::~FinalManagement()
{

}

//Function for reading the tenant's csv file
bool FinalManagement::reading_TenantFile()
{
    string gender,job,delimiter=",",name;
    int age,unit,month,day,year,row=0,col = 0,date_array_index=0,
        payment_status_index=0,tenantArr_index=0;
    double rent;
    char payment_status[6];
    int date_array[3];
    ifstream readFile;
    string line,temp;
    string::size_type wStart,wEnd;
    //open the file
    readFile.open(tenantFileName);
    if(!readFile.is_open())
    {
        readFile.close();
        return false;
    }
    else
    {
        while(readFile.good())
        {     
            if(row==0)//Skip the first row 
            {
                getline(readFile,line);
                row++;
            }
            else
            {
                getline(readFile,line);
                //Find the index of character which is not match the delimiter
                wStart = line.find_first_not_of(delimiter);
                while(wStart<std::string::npos)
                {
                    wEnd = line.find_first_of(delimiter,wStart);
                    temp = line.substr(wStart,wEnd-wStart);
                    wStart= line.find_first_not_of(delimiter,wEnd);
                    if(col==0)//Set tenant's name
                    {
                        name = temp;
                        col++;
                        tenantArr[tenantArr_index].setName(name);
                    }
                    else if(col==1)//Set tenant's age
                    {
                        age = stoi(temp);
                        col++;
                        tenantArr[tenantArr_index].setAge(age);
                    }
                    else if(col==2)//Set tenant's gender
                    {
                        gender = temp;
                        col++;
                        tenantArr[tenantArr_index].setGender(gender);
                    }
                    else if(col==3)//Set tenant's job
                    {
                        job = temp;
                        col++;
                        tenantArr[tenantArr_index].setJob(job);
                    }
                    else if(col==4)//Set tenant's unit Number
                    {
                        unit = stoi(temp);
                        col++;
                        tenantArr[tenantArr_index].setUnitNumber(unit);                    
                    }
                    else if(col==5)//Set tenant's moving in date
                    {
                        stringstream s_stream(temp);
                        string splited_date;
                        while(s_stream.good()) //splite date by '/' month day year
                        {
                            getline(s_stream,splited_date,'/');
                            date_array[date_array_index] = stoi(splited_date);
                            date_array_index++;
                        }
                        for(int x=0;x<3;x++)//get day, month, and year fromthe date_array[3]
                        {
                            if(x==0){month = date_array[x];}
                            else if(x==1){day = date_array[x];}
                            else if(x==2){year = date_array[x];}
                        }
                        date_array_index=0;
                        col++;
                        tenantArr[tenantArr_index].setMovingIn_Date(Date(day,month,year));                        
                    }
                    else if(col==6)//set Monthly Rent
                    {
                        rent = stod(temp);
                        col++;
                        tenantArr[tenantArr_index].setMonthlyRent(rent);
                    }
                    else //set payment's status. Paid = 'p', Not Paid = 'N'
                    {
                        if(temp.compare("Paid")==0)
                        {
                            payment_status[payment_status_index] = 'P';
                        }
                        else
                        {
                        payment_status[payment_status_index] = 'N';
                        }
                        payment_status_index++;  
                        col++;
                    }   
                }
                tenantArr[tenantArr_index].setPaymentStatus(payment_status);
                tenantArr_index++;
            }
            row++;
            col=0;
            payment_status_index=0; 
        } 
    }
    readFile.close(); //Close the file
    return true;
}

//Function for reading the manager's csv file
bool FinalManagement::reading_ManagerFile()
{
    string name,gender,delimiter=",";
    int age,month,day,year,row=0,date_array_index=0,managerArr_index=0,
    expense_index=0;
    double salary,bonus;
    double expense[6];
    int date_array[3];
    ifstream readFile;
    string line,temp;
    string temp_manarger_arr[12],content;
    int temp_manarger_arr_index=0;
    readFile.open(managerFileName);
    if(readFile.is_open())
    {
        while(getline(readFile,line))
        {
            if(row==0)//Skip the first row 
            {
                row++;
            }
            else
            {
                stringstream temp_stream(line);
                while(temp_stream.good())
                {
                    getline(temp_stream,content,',');      
                    temp_manarger_arr[temp_manarger_arr_index] = content;
                    temp_manarger_arr_index++;
                }
                for(int index=0;index<12;index++)
                {
                    if(index==0) //Set manager's name
                    {
                        name = temp_manarger_arr[index];
                        managerArr[managerArr_index].setName(name);
                    }
                    else if(index==1) //Set manager's age
                    {
                        age = stoi(temp_manarger_arr[index]);
                        managerArr[managerArr_index].setAge(age);
                    }
                    else if(index==2) //Set manager's gender
                    {
                        gender = temp_manarger_arr[index];
                        managerArr[managerArr_index].setGender(gender);
                    }
                    else if(index==3) //Set manager's hired date
                    {
                        stringstream s_stream(temp_manarger_arr[index]);
                        string splited_date;
                        while(s_stream.good()) //splite date by '/' month day year
                        {
                            getline(s_stream,splited_date,'/');
                            date_array[date_array_index] = stoi(splited_date);
                            date_array_index++;
                        }
                        for(int x=0;x<3;x++)
                        {
                            if(x==0){month = date_array[x];}
                            else if(x==1){day = date_array[x];}
                            else if(x==2){year = date_array[x];}
                        }
                        date_array_index=0;
                        managerArr[managerArr_index].setHired_Date(Date(day,month,year));
                    }
                    else if(index==4) //Set manager's salary
                    {
                        salary = stod(temp_manarger_arr[index]);
                        managerArr[managerArr_index].setSalary(salary);
                    }
                    else if(index==5) //Set manager's bouns
                    {
                        bonus = stod(temp_manarger_arr[index]);
                        managerArr[managerArr_index].setBouns(bonus);
                    }
                    else //sey manager's expense for each month
                    {
                        expense[expense_index] = stod(temp_manarger_arr[index]);
                        expense_index++;
                    }
                }
                managerArr[managerArr_index].setMonthly_expense(expense);
                managerArr_index++;
                expense_index=0;      
                temp_manarger_arr_index=0; 
            }
        }
        readFile.close();//Close the file
    }
    else
    {
        readFile.close();
        return false;
    }  
    return true;
}

//Function for searching a tenant by his/her name
int FinalManagement::searchTenant(const string& enterName)
{
    for(int index=0;index<MAX_TENANT;index++)
    {
        if(tenantArr[index].getName().compare(enterName)==0)
        {
            displaySingleTenantProfit(index);
            return index;
        }  
    }
    return -1;
}

//Funtion for display a signle profile of a tenants
void FinalManagement::displaySingleTenantProfit(const int& tenantIndex)
{
    cout<< "------------------------"<<endl;
    tenantArr[tenantIndex].printInfo();
    cout<< "------------------------"<<endl;
}

//Function for changing the tenants' field and save all changes to the original csv files
bool FinalManagement::changeTenantField(const int& index_arr,const int& changeOption,string content,int check)
{
    if(changeOption==1)//changeOption = 1, change the tenant's name
    {
        changeTenantOrignalFile(index_arr,changeOption,content,check);
        tenantArr[index_arr].setName(content);   
    }
    else if(changeOption==2)//changeOption = 2, change the tenant's age
    {
        changeTenantOrignalFile(index_arr,changeOption,content,check);
        int change_age = stoi(content);
        tenantArr[index_arr].setAge(change_age);
    }
    else if(changeOption==3) //changeOption = 3, change the tenant's gender
    {
        changeTenantOrignalFile(index_arr,changeOption,content,check);
        tenantArr[index_arr].setGender(content);
    }
    else if(changeOption==4)//changeOption = 4, change the tenant's job
    {
        changeTenantOrignalFile(index_arr,changeOption,content,check);
        tenantArr[index_arr].setJob(content);
    }
    else if(changeOption==5)//changeOption = 5, change the tenant's unit number
    {
        changeTenantOrignalFile(index_arr,changeOption,content,check);
        int change_unit = stoi(content);
        tenantArr[index_arr].setUnitNumber(change_unit);
    }
    else if(changeOption==6)//changeOption = 6, change the tenant's moving date
    {
        changeTenantOrignalFile(index_arr,changeOption,content,check);
        int date_array[3];
        int date_array_index=0,month,day,year;
        stringstream s_stream(content);
        string splited_date;
        while(s_stream.good()) //splite date by '/' month day year
        {
            getline(s_stream,splited_date,'/');
            date_array[date_array_index] = stoi(splited_date);
            date_array_index++;
        }
        for(int x=0;x<3;x++)
        {
            if(x==0){month = date_array[x];}
            else if(x==1){day = date_array[x];}
            else if(x==2){year = date_array[x];}
        }
        tenantArr[index_arr].setMovingIn_Date(Date(day,month,year)); 
    }
    else if(changeOption==7)//changeOption = 7, change the tenant's monthly rent
    {
        changeTenantOrignalFile(index_arr,changeOption,content,check);
        double change_monthlyRent = stod(content);
        tenantArr[index_arr].setMonthlyRent(change_monthlyRent);
    }
    return true;
}

//Function for modifying the orignal tenant csv file
void FinalManagement::changeTenantOrignalFile(int changeRow,int changeColumn,string changeContent,int check)
{
    changeColumn -= 1;
    ofstream outputFile;
    outputFile.open(tenantFileName,ios::out);
    outputFile.clear();
    if(check==1)//If check equal to 1, that means the first six month
    {
        //output the first line of tenants' file
        outputFile<<"Name"<<","<<"Age"<<","<<"Gender"<<","<<"Job"<<","<<"House Unit Number"<<","<<"Moving-in Date"<<","<<"Monthly Rental Fee"<<","<<"January  2020"<<
                ","<<"February  2020"<<","<<"March  2020"<<","<<"April  2020"<<","<<"May  2020"<<","<<"June  2020"<<endl;
    }
    else//The second six month
    {
        //Output the first line of tenants' file
        outputFile<<"Name"<<","<<"Age"<<","<<"Gender"<<","<<"Job"<<","<<"House Unit Number"<<","<<"Moving-in Date"<<","<<"Monthly Rental Fee"<<","<<"July  2020"<<
                ","<<"August  2020"<<","<<"September  2020"<<","<<"October  2020"<<","<<"November  2020"<<","<<"December  2020"<<endl;
    }
    //Output the all information of tenants into current tenants file 
    for(int x=0;x<MAX_TENANT;x++)//row = 100
    {
        for(int y=0;y<13;y++)//column = 13
        {
            //if current row = index of tenants that user want to change and 
            //current column = index of fields that user want to change
            if(x == changeRow && y == changeColumn)
            {
                 outputFile<<changeContent<<",";
            }
            else 
            {
                if(y==0)
                {
                    //Ouput the Tenant's name
                    outputFile<<tenantArr[x].getName()<<",";
                }
                else if(y==1)
                {     
                    //Ouput the Tenant's age
                    outputFile<<tenantArr[x].getAge()<<",";
                }
                else if(y==2)
                {
                    //Ouput the Tenant's gender
                    outputFile<<tenantArr[x].getGender()<<",";
                }
                else if(y==3)
                {
                    //Ouput the Tenant's job
                    outputFile<<tenantArr[x].getJob()<<",";
                }
                else if(y==4)
                {
                    //Ouput the Tenant's unit number
                    outputFile<<tenantArr[x].getUnitNumber()<<",";
                }
                else if(y==5)
                {
                    //Ouput the Tenant's moving date
                    Date temp_Date = tenantArr[x].getmovingIn_Date();
                    string day = to_string(temp_Date.getDay());
                    string month = to_string(temp_Date.getMonth());
                    string year = to_string(temp_Date.getYear());
                    string outputTocsv = month+"/"+day+"/"+year;
                    outputFile<<outputTocsv<<",";
                }
                else if(y==6)
                {
                    //Ouput the Tenant's moving date
                    outputFile<<tenantArr[x].getMonthlyRent()<<",";
                }
                else if(y==7)
                {
                    //Ouput the Tenant's payment status
                    char* ptr = tenantArr[x].getPaymentStatus();
                    char temp = *(ptr+0);
                    if(temp=='P')
                    {
                        outputFile<<"Paid"<<",";
                    }
                    else
                    {
                        outputFile<<"Not Paid"<<",";
                    }     
                }
                else if(y==8)
                {
                    //Ouput the Tenant's payment status
                    char* ptr = tenantArr[x].getPaymentStatus();
                    char temp = *(ptr+1);
                    if(temp=='P')
                    {
                        outputFile<<"Paid"<<",";
                    }
                    else
                    {
                        outputFile<<"Not Paid"<<",";
                    }
                }
                else if(y==9)
                {
                    //Ouput the Tenant's payment status
                    char* ptr = tenantArr[x].getPaymentStatus();
                    char temp = *(ptr+2);
                    if(temp=='P')
                    {
                        outputFile<<"Paid"<<",";
                    }
                    else
                    {
                        outputFile<<"Not Paid"<<",";
                    }
                }
                else if(y==10)
                {
                    //Ouput the Tenant's payment status
                    char* ptr = tenantArr[x].getPaymentStatus();
                    char temp = *(ptr+3);
                    if(temp=='P')
                    {
                        outputFile<<"Paid"<<",";
                    }
                    else
                    {
                        outputFile<<"Not Paid"<<",";
                    }
                }
                else if(y==11)
                {
                    //Ouput the Tenant's payment status
                    char* ptr = tenantArr[x].getPaymentStatus();
                    char temp = *(ptr+4);
                    if(temp=='P')
                    {
                        outputFile<<"Paid"<<",";
                    }
                    else
                    {
                        outputFile<<"Not Paid"<<",";
                    }
                }
                else if(y==12)
                {
                    //Ouput the Tenant's payment status
                    char* ptr = tenantArr[x].getPaymentStatus();
                    char temp = *(ptr+5);
                    if(temp=='P')
                    {
                        outputFile<<"Paid";
                    }
                    else
                    {
                        outputFile<<"Not Paid";
                    }
                }
            }
        }
        outputFile<<endl;//newline
    }
    //close the file
    outputFile.close();
}

//Function for changing the managers' field and save all changes to the original csv files
bool FinalManagement::changeManagerField(const int& index_arr,const int& changeOption,string content,int check)
{
    if(changeOption==1)//changeOption = 1, change the manager's name
    {
        changeManagerOrignalFile(index_arr,changeOption,content,check);
        managerArr[index_arr].setName(content);
    }
    else if(changeOption==2)//changeOption = 2, change the manager's age
    {
        changeManagerOrignalFile(index_arr,changeOption,content,check);
        int change_age = stoi(content);
        managerArr[index_arr].setAge(change_age);
    }
    else if(changeOption==3)//changeOption = 3, change the manager's gender
    {
        changeManagerOrignalFile(index_arr,changeOption,content,check);
        managerArr[index_arr].setGender(content);
    }
    else if(changeOption==4)//changeOption = 4, change the manager's hired date
    {  
        int date_array[3];
        int date_array_index=0,month,day,year;
        changeManagerOrignalFile(index_arr,changeOption,content,check);
        stringstream s_stream(content);
        string splited_date;
        while(s_stream.good()) //splite date by '/' month day year
        {
            getline(s_stream,splited_date,'/');
            date_array[date_array_index] = stoi(splited_date);
            date_array_index++;
        }
        for(int x=0;x<3;x++)
        {
            if(x==0){month = date_array[x];}
            else if(x==1){day = date_array[x];}
            else if(x==2){year = date_array[x];}
        }
        managerArr[index_arr].setHired_Date(Date(day,month,year));
    }  
    return true;
}

//Function for changing the managers' salary and bonus, it will save all changes to the original csv files
bool FinalManagement::changeManagerSalaryBonus(const int& index_arr,const int& changeOption,string content,int check)
{
    if(changeOption==5)//changeOption = 5, change the manager's salary
    {
        changeManagerOrignalFile(index_arr,changeOption,content,check);
        double change_salary = stod(content);
        managerArr[index_arr].setSalary(change_salary);
    }
    else if(changeOption==6)//changeOption = 6, change the manager's bonus
    {
        changeManagerOrignalFile(index_arr,changeOption,content,check);
        double change_bouns = stod(content);
        managerArr[index_arr].setBouns(change_bouns);
    }
    return true;
}

//Function for modifying the orignal manager csv file
void FinalManagement::changeManagerOrignalFile(int changeRow,int changeColumn,string changeContent,int check)
{
    changeColumn -= 1;
    ofstream outputFile;
    outputFile.open(managerFileName,ios::out);
    outputFile.clear();
    if(check==1)//If check equal to 1, that means the first six month
    {
        //output the first line of manager' file
        outputFile<<"Name"<<","<<"Age"<<","<<"Gender"<<","<<"Hired Date"<<","<<"Salary"<<","<<"Bonus"<<","<<"Expense for January 2020"<<","<<"Expense for February 2020"<<
                ","<<"Expense for March 2020"<<","<<"Expense for April 2020"<<","<<"Expense for May 2020"<<","<<"Expense for June 2020"<<endl;
    }
    else//The second six month
    {
        //output the first line of manager' file
        outputFile<<"Name"<<","<<"Age"<<","<<"Gender"<<","<<"Hired Date"<<","<<"Salary"<<","<<"Bonus"<<","<<"Expense for July 2020"<<","<<"Expense for August 2020"<<
                ","<<"Expense for September 2020"<<","<<"Expense for October 2020"<<","<<"Expense for November 2020"<<","<<"Expense for December 2020"<<endl;
    }
    for(int x=0;x<MAX_MANAGER;x++)//total row = 2
    {
        for(int y=0;y<12;y++)//total column = 12
        {
            //if current row = index of manager that user want to change and 
            //current column = index of fields that user want to change
            if(x == changeRow && y == changeColumn)
            {
                 outputFile<<changeContent<<",";
            }
            else 
            {
                if(y==0)
                {
                    //Output the manager's name
                    outputFile<<managerArr[x].getName()<<",";
                }
                else if(y==1)
                {   
                    //Output the manager's age
                    outputFile<<managerArr[x].getAge()<<",";
                }
                else if(y==2)
                {
                    //Output the manager's gender
                    outputFile<<managerArr[x].getGender()<<",";
                }
                else if(y==3)
                {
                    //Output the manager's hired day
                    Date temp_Date = managerArr[x].getHired_Date();
                    string day = to_string(temp_Date.getDay());
                    string month = to_string(temp_Date.getMonth());
                    string year = to_string(temp_Date.getYear());
                    string outputTocsv = month+"/"+day+"/"+year;
                    outputFile<<outputTocsv<<",";
                }
                else if(y==4)
                {
                    //Output the manager's salary
                    outputFile<<managerArr[x].getSalary()<<",";
                }
                else if(y==5)
                {
                    //Output the manager's bonus
                    outputFile<<managerArr[x].getBouns()<<",";
                }
                else if(y==6)
                {
                    //Output the manager's monthly expense
                    double* ptr = managerArr[x].getMonthly_expense();
                    double temp = *(ptr+0);
                    outputFile<<temp<<",";
                }
                else if(y==7)
                {
                    double* ptr = managerArr[x].getMonthly_expense();
                    double temp = *(ptr+1);
                    outputFile<<temp<<",";
                }
                else if(y==8)
                {
                    double* ptr = managerArr[x].getMonthly_expense();
                    double temp = *(ptr+2);
                    outputFile<<temp<<",";
                }
                else if(y==9)
                {
                    double* ptr = managerArr[x].getMonthly_expense();
                    double temp = *(ptr+3);
                    outputFile<<temp<<",";
                }
                else if(y==10)
                {
                    double* ptr = managerArr[x].getMonthly_expense();
                    double temp = *(ptr+4);
                    outputFile<<temp<<",";
                }
                else if(y==11)
                {
                    double* ptr = managerArr[x].getMonthly_expense();
                    double temp = *(ptr+5);
                    outputFile<<temp;
                }
            }
        }
        outputFile<<endl;//newline
    }
    //close file
    outputFile.close();
}

//overridden netIncome function
void FinalManagement::netIncome()
{   
    //reset the totalIncome when function is called
    totalIncome = 0.0;
    double netIncome_currentMonth=0.0,totalRent_currentMonth=0.0,
        salaries_bouns_currentMonth=0.0,expense_currentMonth=0.0;
    int MAX_MONTH_INDEX=6;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<" Net Income: $"<<fixed<<setprecision(2);
        for(int current_tenant=0;current_tenant<MAX_TENANT;current_tenant++)
        {
            //char type pointer ptr that point to first element of payment_status array;
            char* ptr = tenantArr[current_tenant].getPaymentStatus(); 
            //check whether the rent has been paid or not
            if(checkPaymentStatus(*(ptr+current_month)))
            {
                totalRent_currentMonth += tenantArr[current_tenant].getMonthlyRent();
            }
        }
        for(int current_manager=0;current_manager<MAX_MANAGER;current_manager++)
        {
            //accumulate salary and bonuses
            salaries_bouns_currentMonth += managerArr[current_manager].getSalary();
            salaries_bouns_currentMonth += managerArr[current_manager].getBouns();
            //double type pointer ptr that point to first element of monthly_expense array;
            double* ptr = managerArr[current_manager].getMonthly_expense();
            expense_currentMonth += *(ptr+current_month);
        }
        //add total rent that has been collected in current month
        netIncome_currentMonth += totalRent_currentMonth;
        //deduct total salaries and bonuses in current month
        netIncome_currentMonth -= salaries_bouns_currentMonth;
        //deduct total expense in current month
        netIncome_currentMonth -= expense_currentMonth;
        //accumulate each months' netincome
        totalIncome += netIncome_currentMonth;
        cout<<netIncome_currentMonth<<endl;
        //reset variables  
        totalRent_currentMonth=0.0;
        netIncome_currentMonth=0.0;
        expense_currentMonth=0.0;
        salaries_bouns_currentMonth=0.0;
    }
}

//Display the summary of the financial statement for a year: total revenue (total rental fees), 
//total expense, earning before tax, tax (12%), and earning after tax
double* FinalManagement::financialStatement()
{
    double netIncome_currentMonth=0.0,totalRent_currentMonth=0.0,
           salaries_bouns_currentMonth=0.0,expense_currentMonth=0.0,
           tax = 0.12,temp_totalIncome=0.0;
    int MAX_MONTH_INDEX=6;
    //when financialStatement_callTimes=1, that means current function has been called once
    //then reset the financial_arr array
    if(financialStatement_callTimes == 1)
    {
        for(int x=0;x<5;x++)
        {
            financial_arr[x] = 0.0;
        }
        financialStatement_callTimes=0;//reset the financialStatement_callTimes to 0
    }
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        for(int current_tenant=0;current_tenant<MAX_TENANT;current_tenant++)
        {
            //char type pointer ptr that point to first element of payment_status array;
            char* ptr = tenantArr[current_tenant].getPaymentStatus(); 
            //check whether the rent has been paid or not
            if(checkPaymentStatus(*(ptr+current_month)))
            {
                totalRent_currentMonth += tenantArr[current_tenant].getMonthlyRent();
            }
        }
        financial_arr[0]+= totalRent_currentMonth;
        for(int current_manager=0;current_manager<MAX_MANAGER;current_manager++)
        {
            //accumulate salary and bonuses
            salaries_bouns_currentMonth += managerArr[current_manager].getSalary();
            salaries_bouns_currentMonth += managerArr[current_manager].getBouns();
            //double type pointer ptr that point to first element of monthly_expense array;
            double* ptr = managerArr[current_manager].getMonthly_expense();
            expense_currentMonth += *(ptr+current_month);
        }
        financial_arr[1]+= salaries_bouns_currentMonth;
        financial_arr[1]+= expense_currentMonth;
        //add total rent that has been collected in current month
        netIncome_currentMonth += totalRent_currentMonth;
        //deduct total salaries and bonuses in current month
        netIncome_currentMonth -= salaries_bouns_currentMonth;
        //deduct total expense in current month
        netIncome_currentMonth -= expense_currentMonth;
        //accumulate each months' netincome
        temp_totalIncome += netIncome_currentMonth;
        //reset variables  
        totalRent_currentMonth=0.0;
        netIncome_currentMonth=0.0;
        expense_currentMonth=0.0;
        salaries_bouns_currentMonth=0.0;
    }
    financial_arr[2]+= temp_totalIncome;
    financial_arr[3]+= (temp_totalIncome*tax);
    financial_arr[4]+= (temp_totalIncome*(1-tax));
    financialStatement_callTimes++;
    return financial_arr;
}

//overridden collectRentalFee function
void FinalManagement::collectRentalFee()
{
    totalRent=0.0;
    double rent_currentMonth=0.0;
    int MAX_MONTH_INDEX=6;
    char* ptr;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        for(int current_tenant=0;current_tenant<MAX_TENANT;current_tenant++)
        {
            ptr = tenantArr[current_tenant].getPaymentStatus();
            //Check current tenants whether paid the rent
            if(checkPaymentStatus(*(ptr+current_month)))
            {
                rent_currentMonth += tenantArr[current_tenant].getMonthlyRent();
            }
            else
            {
                rent_currentMonth += 0.0;
            }
        }
        cout<<month_name[current_month]<<": $"<<fixed<<setprecision(2)<<rent_currentMonth<<endl;
        totalRent+=rent_currentMonth;
        rent_currentMonth = 0.0;
    }
}

//overridden managerSalary_bouns function
void FinalManagement::managerSalary_bouns()
{
    totalSalarayBonus_Expense = 0.0;
    double current_salaries_Bonuses=0.0;
    int MAX_MONTH_INDEX=6;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<": $"<<fixed<<setprecision(2);
        for(int current_manager=0;current_manager<MAX_MANAGER;current_manager++)
        {
            current_salaries_Bonuses += managerArr[current_manager].getSalary();
            current_salaries_Bonuses += managerArr[current_manager].getBouns();
        }
        cout<<current_salaries_Bonuses<<endl;
        totalSalarayBonus_Expense += current_salaries_Bonuses;
        current_salaries_Bonuses=0;
    }
}

//overridden totalExpense function
void FinalManagement::totalExpense()
{
    totalManager_Expense = 0.0;
    int MAX_MONTH_INDEX=6;
    double expense_currentMonth=0.0;
    double* ptr;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<": $"<<fixed<<setprecision(2);
        for(int current_manager=0;current_manager<MAX_MANAGER;current_manager++)
        {
            ptr = managerArr[current_manager].getMonthly_expense();
            expense_currentMonth += *(ptr+current_month);
        }
        cout<<fixed<<setprecision(2)<<expense_currentMonth<<endl;
        totalManager_Expense += expense_currentMonth;
        expense_currentMonth=0.0;
    }
}

//overridden missingRental function
void FinalManagement::missingRental()
{
    total_missRent = 0.0;
    int MAX_MONTH_INDEX=6;
    double missRent_currentMonth=0.0;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<": $";
        for(int current_tenant=0;current_tenant<MAX_TENANT;current_tenant++)
        {
            char* ptr = tenantArr[current_tenant].getPaymentStatus();
            if(!checkPaymentStatus(*(ptr+current_month)))
            {
                missRent_currentMonth += tenantArr[current_tenant].getMonthlyRent();
            }
        }
        cout<<fixed<<setprecision(2)<<missRent_currentMonth<<endl;
        total_missRent += missRent_currentMonth;
        missRent_currentMonth=0.0;
    }
}

//overridden listTenantsNotPay function
void FinalManagement::listTenantsNotPay()
{
    //if listNotPayFunction_callTimes = 2, that means the functions has been called twice
    if(listNotPayFunction_callTimes == 2)
    {  
        //reset the vector
        notPay_tenants_index.clear();
        accumulate_Amount.clear();
        //reset the listNotPayFunction_callTimes
        listNotPayFunction_callTimes = 0;
    }
    int MAX_MONTH_INDEX=6,MAX_TENANTS_INDEX=100;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<"--------------------------------------------------"<<endl;
        cout<<month_name[current_month]<<endl;
        for(int current_tenant=0;current_tenant<MAX_TENANT;current_tenant++)
        {        
            char* ptr = tenantArr[current_tenant].getPaymentStatus();
            if(!checkPaymentStatus(*(ptr+current_month)))
            {  
                int find_indexOfTenantsInVector = checkExist_NotPayTentants(current_tenant);
                if(find_indexOfTenantsInVector!=-1)
                {
                    double temp = accumulate_Amount[find_indexOfTenantsInVector];
                    accumulate_Amount[find_indexOfTenantsInVector] = temp+tenantArr[current_tenant].getMonthlyRent();
                }
                else
                {
                    notPay_tenants_index.push_back(current_tenant);
                    accumulate_Amount.push_back(tenantArr[current_tenant].getMonthlyRent());
                }
                cout<<"Tenant Name: "<<tenantArr[current_tenant].getName()<<endl;
                cout<<"Unit#: "<<tenantArr[current_tenant].getUnitNumber()<<endl;
                cout<<"Monthly Rent: $"<<tenantArr[current_tenant].getMonthlyRent()<<endl;
                displayTotalRentTenantsOwe(current_tenant);
                cout<<endl;
            }
        }
    }
    listNotPayFunction_callTimes++; 
}

//Display the accumulating rental fee that a tenant owe
void FinalManagement::displayTotalRentTenantsOwe(const int& tenants_index)
{
    for(int index=0;index<notPay_tenants_index.size();index++)
    {
        if(notPay_tenants_index[index]==tenants_index)
        {
            cout<<"Accumulative Debts Total For A Year: $"<<accumulate_Amount[index]<<endl;
            break;
        }       
    }
}

//Check the otPay_tenants_index vector whether contain the current index of tenants
int FinalManagement::checkExist_NotPayTentants(const int& tenants_index)
{
    auto result = find(notPay_tenants_index.begin(),notPay_tenants_index.end(),tenants_index);
    if(result!= notPay_tenants_index.end())
    {
        int index = result-notPay_tenants_index.begin();
        return index;
    } 
    return -1;
}

//function that returns the Manager's name
string FinalManagement::getManagerName(const int& index_arr)
{
    return (managerArr[index_arr].getName());
}

//Accessors
//return the totalrent
double FinalManagement::getTotalRent() const
{
    return totalRent;
}

//return total expense
double FinalManagement::getTotalExpense() const
{
    return totalManager_Expense;
}

//return total miss rent
double FinalManagement::getTotalMissRent() const
{
    return total_missRent;
}

//return totalSalarayBonus_Expense
double FinalManagement::getTotalSalarayBonus() const
{
    return totalSalarayBonus_Expense;
}

//return totalIncome
double FinalManagement::getTotalIncome() const
{
    return totalIncome;
}
