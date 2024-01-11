#pragma once
#include <algorithm>
#include <vector>
#include "Student.h"

class Group
{
  int number;
  std::vector<std::shared_ptr<Student>> students;

public:
  Group(int number) : number(number)
  {
  }
  int getNumber() 
  {
    return number;
  }
  std::vector<std::shared_ptr<Student>> getAllStudents() const
  {
    return students;
  }

  void addStudentToGroup(std::unique_ptr<Student> student) {
    students.push_back(std::move(student));
  }

  int removeStudentFromGroup(std::shared_ptr<Student> student)
  {
    auto it = std::find(students.begin(), students.end(), student);
      if (it == students.end()) return 0;
      students.erase(it); return 1;
  }
};