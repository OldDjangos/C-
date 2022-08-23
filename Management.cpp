/*
 *Tititle: COMP3140 Project Stage 2
 *File name: Management.cpp
 *File Type: Implement File 
 *Date: 11/20/2020
 */
#include <string>
#include <iostream>
#include "Management.h"

using namespace std;

//Parameter constructor, takes in a file name as a string.
Management::Management(const string& newFileName)
:fileName(newFileName),totalManager_Expense(0.0),totalRent(0.0),totalSalarayBonus_Expense(0.0)
{

}

//Default constructor
Management::Management()
:fileName(""),totalManager_Expense(0.0),totalRent(0.0),totalSalarayBonus_Expense(0.0)
{

} 

//Destructor
Management::~Management()
{

}

//Print out all tenants' profile.
void Management::profile_tenant()
{ 
    for(int index=0;index<100;index++)
    {
       tenantArr[index].printInfo();
    }
}

//Print out all Manager' profile.
void Management::profile_manager()
{
    for(int index=0;index<2;index++)
    {
       managerArr[index].printInfo();
       cout<<endl;
    }
}

//Mutators
void Management::setFileName(const string& newFileName)
{
    fileName = newFileName;
}

//Accessors
string Management::getFileName()
{
    return fileName;
}







