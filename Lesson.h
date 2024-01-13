#pragma once
#include "Group.h"

public:
    std::string time;
    int laneNumber;
    std::string instructorName;
    int groupNumber;

public:
    Lesson(const std::string time, const int laneNumber, const std::string& instructorName, const int groupNumber)
        :  time(time), laneNumber(laneNumber), instructorName(instructorName), groupNumber(groupNumber) {}

    std::string getTime() const
    {
        return time;
    }

    int getLaneNumber() const
    {
        return laneNumber;
    }

    std::string getInstructorName() const
    {
        return instructorName;
    }

    int getGroupNumber() const
    {
        return groupNumber;
    }
};

class DailySchedule 
{
public:
    std::string day;
    std::vector<Lesson> lessons;

    DailySchedule(const std::string& day, std::vector<Lesson> lessons) : day(day), lessons(lessons) {}
};

class WeeklySchedule 
{
public:
    std::vector<DailySchedule> days;
};

void printSchedule(const WeeklySchedule& schedule)
{
    std::cout << "======================= Weekly Schedule =======================\n\n";
    std::cout << "---------------------------------------------------------------\n";
    std::cout << std::setw(15) << std::left << "Time";
    std::cout << std::setw(15) << std::left << "Lane number";
    std::cout << std::setw(20) << std::left << "Instructor";
    std::cout << std::setw(15) << std::left << "Group number";
    std::cout << "\n---------------------------------------------------------------\n";

    for (const auto& day : schedule.days) {
        std::cout << std::setw(10) << std::left << day.day;

        if (day.lessons.empty()) {
            std::cout << std::setw(15) << std::left << "No lessons for this day.";
            std::cout << "\n---------------------------------------------------------------\n";
        }
        else {
            for (const auto& lesson : day.lessons) {
                std::cout << std::endl;
                std::cout << std::setw(15) << std::left << lesson.time;
                std::cout << std::setw(15) << std::left << lesson.laneNumber;
                std::cout << std::setw(20) << std::left << lesson.instructorName;
                std::cout << std::setw(15) << std::left << lesson.groupNumber;
                std::cout << "\n";
            }
            std::cout << "---------------------------------------------------------------\n";
        }
    }
}
