#pragma once
#include <iostream>

class Student
{
  std::string firstName;
  std::string lastName;
  std::string parentName;
  std::string phoneNumber;
  int paidLessons;

public:
  Student(std::string _firstName, std::string _lastName, std::string _parentName, std::string _phoneNumber, int _paidLessons)
    : phoneNumber(_phoneNumber), paidLessons(_paidLessons)
  { // Also make the "parentName" and "lastName" as : first letter is upper, all other are lower case.
	  std::transform(_firstName.begin(), _firstName.end(), _firstName.begin(),[](unsigned char c) { return std::tolower(c); });
	  std::transform(_lastName.begin(), _lastName.end(), _lastName.begin(),[](unsigned char c) { return std::tolower(c); });
	  std::transform(_parentName.begin(), _parentName.end(), _parentName.begin(),[](unsigned char c) { return std::tolower(c); });
    _firstName[0] = std::toupper(_firstName[0]), _lastName[0] = std::toupper(_lastName[0]), _parentName[0] = std::toupper(_parentName[0]);
    firstName = _firstName, lastName = _lastName, parentName = _parentName;
  }

    std::string getFirstName() const 
    {
      return firstName;
    }
    std::string getLastName() const 
    {
      return lastName;
    }
    std::string getParentName() const 
    {
      return parentName;
    }
    std::string getPhoneNumber() const 
    {
      return phoneNumber;
    }
    int getPaidLessons() const 
    {
      return paidLessons;
    }

    void setFirstName(std::string _firstN) 
    {
      firstName = _firstN;
    }
    void setLastName(std::string _lastN) 
    {
      lastName = _lastN;
    }
    void setParentName(std::string _parentN) 
    {
      parentName = _parentN;
    }
    void getPhoneNumber(std::string _phoneN)
    {
      phoneNumber = _phoneN;
    }

    bool operator== (const Student& _obj)
    {
      return ((firstName == _obj.getFirstName()) && (lastName == _obj.getLastName()) && (parentName == _obj.getParentName()));
    }
};