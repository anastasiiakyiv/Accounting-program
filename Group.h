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

  void addStudentToGroup(std::shared_ptr<Student> student) {
    // std::cout << "GROUP | addStudentToGroup | student.get()->getLastName() = " << student.get()->getLastName() << std::endl;
    students.push_back(student);
    // for (auto _student : students) {
    // //    std::cout << "GROUP | addStudentToGroup | INLOOP | student.get()->getLastName() = " << _student.get()->getLastName() << std::endl;
    // }
  }

  int removeStudentFromGroup(std::shared_ptr<Student> student)
  {
    auto it = std::find(students.begin(), students.end(), student);
      if (it == students.end()) return 0;
      students.erase(it); return 1;
  }
};