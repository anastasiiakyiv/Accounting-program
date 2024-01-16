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
  
void removeStudentFromGroup(const std::string& lastName) {
    auto it = std::remove_if(students.begin(), students.end(),
        [lastName](const std::shared_ptr<Student>& student)
        { return student->getLastName() == lastName; });

    if (it != students.end()) {
        int groupNumber = getNumber();
        students.erase(it, students.end());
        std::cout << "Student with the last name \"" << lastName << "\" has been successfully removed from the Group " << groupNumber << "." << std::endl;
    }
    else {
        int groupNumber = getNumber();
        std::cout << "Student with the last name \"" << lastName << "\" was not found in the Group " << groupNumber << "." << std::endl;
    }
}
};
