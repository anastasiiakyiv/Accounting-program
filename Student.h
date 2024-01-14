#pragma once
#include <iostream>

class Student
{
  std::string lastName;
  std::string parentName;
  std::string phoneNumber;
  int paidLessons;

public:
  Student(std::string _lastName, std::string _parentName, std::string _phoneNumber, int _paidLessons)
    : phoneNumber(_phoneNumber), paidLessons(_paidLessons)
  { // Also make the "parentName" and "lastName" as : first letter is upper, all other are lower case.
	  std::transform(_lastName.begin(), _lastName.end(), _lastName.begin(),[](unsigned char c) { return std::tolower(c); });
	  std::transform(_parentName.begin(), _parentName.end(), _parentName.begin(),[](unsigned char c) { return std::tolower(c); });
    _lastName[0] = std::toupper(_lastName[0]), _parentName[0] = std::toupper(_parentName[0]);
    lastName = _lastName, parentName = _parentName;
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
};