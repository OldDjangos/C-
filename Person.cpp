/*
 *Tititle: COMP3140 Project Stage 2
 *File name: Person.cpp
 *File Type: Implement File 
 *Date: 11/20/2020
 */
#include <string>
#include <iostream>
#include "Person.h"

using namespace std;

//Parameter Constructor
Person::Person(const string& newName,const int& newAge,const string& newGender)
:name(newName),age(newAge),gender(newGender)
{

}

//Default Constructor
Person::Person()
:name(""),age(0),gender("")
{

}

//Destructors
Person::~Person()
{
    
}

//Mutators
void Person::setName(string& newName)
{
    name = newName;
}

void Person::setAge(int& newAge)
{
    age = newAge;
}
void Person::setGender(string& newGender)
{
    gender = newGender;
}

//Accessors
int Person::getAge() const
{
    return age;
}

string Person::getName() const
{
    return name;
}
string Person::getGender() const
{
    return gender;
}

//printInfo() function that print all member data
void Person::printInfo() const
{
    cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Gender: "<<gender<<endl;
}