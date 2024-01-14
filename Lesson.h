#pragma once
#include "Lane.h"
#include "Instructor.h"
#include "Group.h"

class Lesson
{
public:
    std::string time;
    std::shared_ptr<Lane> lane;
    std::shared_ptr<Instructor> instructorName;
    std::shared_ptr<Group> groupNumber;

public:
    Lesson(const std::string time, std::shared_ptr<Lane> lane, std::shared_ptr<Instructor> instructorName, std::shared_ptr<Group> groupNumber)
        : time(time), lane(lane), instructorName(instructorName), groupNumber(groupNumber) {}

    std::string getTime() const
    {
        return time;
    }

    std::shared_ptr<Lane> getLane() const
    {
        return lane;
    }

    std::shared_ptr<Instructor> getInstructorName() const
    {
        return instructorName;
    }

    std::shared_ptr<Group> getGroupNumber() const
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

void printSchedule(std::ostream& os, const WeeklySchedule& schedule, std::string timestamp = "")
{
    os << std::endl << timestamp << std::string(5, '=') << std::setw(35) << std::left << " Generalized weekly schedule. " 
    << std::string(9,'=') << "\n\n" << std::string(73, '-') << "\n"
    << std::setw(16) << std::left << "Time"
    << std::setw(16) << std::left << "|Lane number"
    << std::setw(21) << std::left << "|Instructor"
    << std::setw(15) << std::left << "|Group number" << "    |"
    << "\n-------------------------------------------------------------------------\n";

    for (const auto& day : schedule.days) {
        os << std::setw(10) << std::left << day.day 
           << "                                                              |"
           << "\n-------------------------------------------------------------------------";

        if (day.lessons.empty()) {
           os << std::setw(15) << std::left << "No lessons for this day."
           << "\n-------------------------------------------------------------------------\n";
        }
        else {
            for (const auto& lesson : day.lessons) {
                os << std::endl
                   << "|" << std::setw(15) << std::left << lesson.time
                   << "|" << std::setw(15) << std::left << lesson.lane->getLaneNumber()
                   << "|" << std::setw(20) << std::left << lesson.instructorName->getLastName()
                   << "|" << std::setw(15) << std::left << lesson.groupNumber->getNumber() << "\t|";
            }
            os << "\n"
               << "-------------------------------------------------------------------------\n";
        }
    }
}

void printScheduleForGroupOrLane(const WeeklySchedule& schedule, char option, int groupOrLaneNumber)
{
    std::string optionLabel;
    std::string optionHeader;
    if (option == 'g') {
        optionLabel = "Group";
        optionHeader = "Lane Number";
    }
    else if (option == 'l') {
        optionLabel = "Lane";
        optionHeader = "Group Number";
    }
    else {
        std::cerr << "Invalid option. Use 'g' for group or 'l' for lane.\n";
        return;
    }

    std::cout << "\n====================== Weekly Schedule for " << optionLabel << " " << groupOrLaneNumber << " ======================\n";
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(16) << "Day" << std::setw(16) << "|Time" << std::setw(21) << "|" + optionHeader << std::setw(19) << "|Instructor" << "|";
    std::cout << "\n-------------------------------------------------------------------------\n";
    for (const auto& day : schedule.days) {
        for (const auto& lesson : day.lessons) {
            if (option == 'g' && lesson.groupNumber->getNumber() == groupOrLaneNumber)
            {
                std::cout 
                    << std::left << std::setw(16) << day.day
                    << "|" << std::setw(15) << lesson.time
                    << "|" << std::setw(20) << lesson.lane->getLaneNumber()
                    << "|" << std::setw(18) << lesson.instructorName->getLastName() << "|" << "\n";
            }

            else if (option == 'l' && lesson.lane->getLaneNumber() == groupOrLaneNumber)
            {
                std::cout << "Day: " << day.day << "\n";
                std::cout << "Time: " << lesson.time << "\n";
                std::cout << "Group number: " << lesson.groupNumber->getNumber() << "\n";
                std::cout << "Instructor: " << lesson.instructorName->getLastName() << "\n\n";
            }

        }
    }
    std::cout << "=========================================================================\n";
}
