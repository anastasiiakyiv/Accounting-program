#pragma once
#include <iostream>

class Student
{
  std::string lastName;
  std::string parentName;
  std::string phoneNumber;
  int paidLessons;

public:
  Student(std::string lastName, std::string parentName, std::string phoneNumber, int paidLessons)
    : lastName(lastName), parentName(parentName), phoneNumber(phoneNumber), paidLessons(paidLessons)
  {
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