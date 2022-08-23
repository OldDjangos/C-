/*
 *Tititle: COMP3140 Project Stage 1
 *File name: Person.h
 *File Type: Interface File 
 *Date: 11/13/2020
 */
#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;

class Person
{
    protected:
        string name;
        string gender;
        int age;
    public:
        //Parameter Constructor
        Person(const string& newName,const int& newAge,const string& newGender);
        //Default Constructors
        Person();
        //Destructors
        virtual ~Person();
        //Mutators
        void setName(string& newName);
        void setAge(int& newAge);
        void setGender(string& newGender);
        //Accessors
        int getAge() const;
        string getName() const;
        string getGender() const;
        //printInfo() function that print all member data
        virtual void printInfo() const;
};
#endif