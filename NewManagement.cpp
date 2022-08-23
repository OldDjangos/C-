/*
 *Tititle: COMP3140 Project Stage 1
 *File name: Management.cpp
 *File Type: Implement File 
 *Date: 11/20/2020
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "NewManagement.h"
#include "Tenant.h"
#include "Manager.h"

using namespace std;

//Parameter constructor, takes in two file names as a string.
NewManagement::NewManagement(const string& newTenant_FileName,const string& newManager_FileName)
:Management(""),tenantFileName(newTenant_FileName),managerFileName(newManager_FileName),total_missRent(0.0),
totalIncome(0.0)
{
    
}

//Default constructor
NewManagement::NewManagement()
:Management(""),tenantFileName(""),managerFileName(""),total_missRent(0.0),totalIncome(0.0)
{

}

//Destructor
NewManagement::~NewManagement()
{

}

//Set current six month's name from file
void NewManagement::setMonth_Name()
{
    string line,content;
    ifstream readFile;
    string temp_string[12];
    //open the Manager File
    readFile.open(managerFileName);
    getline(readFile,line);
    readFile.close();
    stringstream temp_stream(line);
    int index=0;
    while(temp_stream.good())
    {
        //split string varable line by delimiter ','
        getline(temp_stream,content,',');
        //put current chunk of variable line into the string array temp_string   
        temp_string[index] = content;
        index++;
    }
    for(int x=6;x<12;x++)
    {
        //cut off "Expense for "
        month_name[x-6] = temp_string[x].substr(12); 
    }
    
}

//Takes in an input file based on the tenantFileName variable, scans through it and 
//put data into tenantArr[100] with any tenats.
void NewManagement::readTenantFile()
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
    readFile.close(); //Close the file
}

//Takes in an input file based on the managerFileName variable, scans through it and 
//put data into managerArr[2] with any tenats
void NewManagement::readManagerFile()
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

//Scans through tenantArr[100] and checks their payment status, if it's true it checks their rental fee and adds it to a total
//for the month as well as a total for 6 months. Does this process 6 times for each month.
void NewManagement::collectRentalFee()
{
    double rent_currentMonth=0.0;
    int MAX_MONTH_INDEX=6,MAX_TENANTS_INDEX=100;
    cout<<"The collected rental fees in total for each month:"<<endl;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        for(int current_tenant=0;current_tenant<MAX_TENANTS_INDEX;current_tenant++)
        {
            char* ptr = tenantArr[current_tenant].getPaymentStatus();
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
    cout<<"The collected rental fees in total for six month: $"<<fixed<<setprecision(2)<<totalRent<<endl;
}

//Scans through the tenantArr[100] and lists any tenants, along with their current index, with payment status set to false(Not Pay).
void NewManagement::listTenantsNotPay()
{
    int MAX_MONTH_INDEX=6,MAX_TENANTS_INDEX=100;
    cout<<"The list of the tenants who did not pay their rental fees:"<<endl;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<endl;
        for(int current_tenant=0;current_tenant<MAX_TENANTS_INDEX;current_tenant++)
        {        
            char* ptr = tenantArr[current_tenant].getPaymentStatus();
            if(!checkPaymentStatus(*(ptr+current_month)))
            {      
                cout<<"Tenant Name: "<<tenantArr[current_tenant].getName()<<endl;
                cout<<"Amount: $"<<tenantArr[current_tenant].getMonthlyRent()<<endl;
            }
        }
        cout<<endl;
    }
}

//This function to determine who hasn't paid their rent, then adds up the total missing rent for the month
//then continues to add the total of missing rent for the past 6 months before printing it out.
void NewManagement::missingRental()
{
    int MAX_MONTH_INDEX=6,MAX_TENANTS_INDEX=100;
    double missRent_currentMonth=0.0;
    cout<<"The amount of missing rental fees in total for each month and for six months:"<<endl;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<": $";
        for(int current_tenant=0;current_tenant<MAX_TENANTS_INDEX;current_tenant++)
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
    cout<<"Total amount if missing rental fees for six months: $"<<fixed<<setprecision(2)<<total_missRent<<endl;
}

//Scans through the managerArr[100] and grabs the total expenses data held in every manager then adds them together and displays the total. 
//It continues to do this for every month as well as the past 6 months.
void NewManagement::totalExpense()
{
    int MAX_MONTH_INDEX=6,MAX_MANAGER_INDEX=2;
    double expense_currentMonth=0.0;
    double* ptr;
    cout<<"Total expense for each month:"<<endl;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<": $"<<fixed<<setprecision(2);
        for(int current_manager=0;current_manager<MAX_MANAGER_INDEX;current_manager++)
        {
            ptr = managerArr[current_manager].getMonthly_expense();
            expense_currentMonth += *(ptr+current_month);
        }
        cout<<fixed<<setprecision(2)<<expense_currentMonth<<endl;
        totalManager_Expense += expense_currentMonth;
        expense_currentMonth=0.0;
    }
    cout<<"Total expense for six months: $"<<fixed<<setprecision(2)<<totalManager_Expense<<endl;
}

//Scans through the managerArr[100] and displays the total salary and bonus of every month as well as 6 months. 
//It does this for every individual manager.
void NewManagement::managerSalary_bouns()
{
    double current_salaries_Bonuses=0.0;
    int MAX_MONTH_INDEX=6,MAX_MANAGER_INDEX=2;
    cout<<"Both Managers' salaries and bonuses in total for each month:"<<endl;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<": $"<<fixed<<setprecision(2);
        for(int current_manager=0;current_manager<MAX_MANAGER_INDEX;current_manager++)
        {
            current_salaries_Bonuses += managerArr[current_manager].getSalary();
            current_salaries_Bonuses += managerArr[current_manager].getBouns();
        }
        cout<<current_salaries_Bonuses<<endl;
        totalSalarayBonus_Expense += current_salaries_Bonuses;
        current_salaries_Bonuses=0;
    }
    cout<<"Total managers' salaries and bonuses in six month: $"<<fixed<<setprecision(2)<<totalSalarayBonus_Expense<<endl;
}

//The function that caculate the total Net income for each month and for six months.
//NetIncome = (total rent collection)- (managers expense)-(salary and bonus expense)
void NewManagement::netIncome()
{
    double netIncome_currentMonth=0.0,totalRent_currentMonth=0.0,
        salaries_bouns_currentMonth=0.0,expense_currentMonth=0.0;
    int MAX_MONTH_INDEX=6,MAX_MANAGER_INDEX=2,MAX_TENANTS_INDEX=100;
    cout<<"Net income for each month:"<<endl;
    for(int current_month=0;current_month<MAX_MONTH_INDEX;current_month++)
    {
        cout<<month_name[current_month]<<" Net Income: $"<<fixed<<setprecision(2);
        for(int current_tenant=0;current_tenant<MAX_TENANTS_INDEX;current_tenant++)
        {
            //char type pointer ptr that point to first element of payment_status array;
            char* ptr = tenantArr[current_tenant].getPaymentStatus(); 
            //check whether the rent has been paid or not
            if(checkPaymentStatus(*(ptr+current_month)))
            {
                totalRent_currentMonth += tenantArr[current_tenant].getMonthlyRent();
            }
        }
        for(int current_manager=0;current_manager<MAX_MANAGER_INDEX;current_manager++)
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
    cout<<"Total Net income for six months: $"<<fixed<<setprecision(2)<<totalIncome<<endl;
}

//Check the tenant's payment status
bool NewManagement::checkPaymentStatus(char payment_state)
{
    if(payment_state=='N')
    {
        return false;
    }
    return true;
}

//Mutators
void NewManagement::setTenantFileName(const string& newTenant_FileName)
{
    tenantFileName = newTenant_FileName;
}

void NewManagement::setManagerFileName(const string& newManager_FileName)
{
    managerFileName = newManager_FileName;
}
//Accessors
string NewManagement::getTenantFileName()
{
    return tenantFileName;
}

string NewManagement::getManagerFileName()
{
    return managerFileName;
}