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
        students.push_back(student);
    }
  
   bool removeStudentFromGroup(std::shared_ptr<Student> student)
   {
    // auto it = std::find(students.begin(), students.end(), student);
    //   if (it == students.end()) return 0;
    //   students.erase(it); return 1;

    // std::vector<std::shared_ptr<MyType>> v;
    // // init v here;
    // MyType my_value;
    // // init my_value here;
    // auto it = std::find_if(v.begin(), v.end(), [&](std::shared_ptr<MyType> const& p) {
    //     return *p == my_value; // assumes MyType has operator==
    // });
    // if (it != v.end()) { /* do what you want with the value found */ }

    // std::vector<std::shared_ptr<MyType>> v;
    // init v here;
    // MyType my_value;
    // init my_value here;

    auto it = std::find_if(students.begin(), students.end(), [&](std::shared_ptr<Student> const& p) {
        return *p == *student; // assumes MyType has operator==
    });
    if (it != students.end()) { 
         /* do what you want with the value found */ 
        students.erase(it, students.end());
     }
    return true;
   }

   bool operator== (Group& _obj)
    {
      return (number == _obj.getNumber());
    }
};
