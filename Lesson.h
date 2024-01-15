#pragma once
#include <memory>
#include "Lane.h"
#include "Instructor.h"
#include "Group.h"

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"      /* Yellow */

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

void printSchedule(std::ostream& os, std::shared_ptr<WeeklySchedule> schedule, std::string timestamp = "", bool color = false)
{
    os << (color ? BLUE : "" ) << std::endl << timestamp << std::string(5, '=') 
    << std::setw(30) << std::left << " Generalized weekly schedule. " 
    << std::string(18,'=') << "\n\n" << std::string(77, '-') << "\n"
    << std::setw(17) << std::left << "| Time"
    << std::setw(16) << std::left << "| Lane number"
    << std::setw(21) << std::left << "| Instructor"
    << std::setw(18) << std::left << "| Group number" << "    |"
    << "\n-----------------------------------------------------------------------------\n" << (color ? RESET : "" );

    for (const auto& day : schedule.get()->days) {
        os << (color ? BLUE : "" ) << std::setw(10) << std::left << day.day 
           << "                                                                  |"
           << "\n-----------------------------------------------------------------------------" << (color ? RESET : "" );

        if (day.lessons.empty()) {
           os << (color ? BLUE : "" ) << std::setw(15) << std::left << "No lessons for this day."
           << "\n-----------------------------------------------------------------------------\n" << (color ? RESET : "" );
        }
        else {
            for (const auto& lesson : day.lessons) {
                os << (color ? YELLOW : "" ) << std::endl
                   << "|" << std::setw(16) << std::left << lesson.time
                   << "|" << std::setw(15) << std::left << lesson.lane->getLaneNumber()
                   << "|" << std::setw(20) << std::left << lesson.instructorName->getLastName()
                   << "|" << std::setw(15) << std::left << lesson.groupNumber->getNumber() << "\t|" << (color ? RESET : "" );
            }
            os << (color ? BLUE : "" ) << "\n"
               << "-----------------------------------------------------------------------------\n" << (color ? RESET : "" );
        }
    }
}

void printScheduleForGroupOrLane(std::ostream& os, std::shared_ptr<WeeklySchedule> schedule, char option, int groupOrLaneNumber, std::string timestamp = "")
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

    // os << "\n====================== Weekly Schedule for " << optionLabel << " " << groupOrLaneNumber << " ======================\n"
    os << std::endl << timestamp << std::string(5,'=') << " Weekly Schedule for " << optionLabel << " " << groupOrLaneNumber 
       << " " << std::string(15,'=') << std::endl
       << "-------------------------------------------------------------------------\n"
       << std::left << std::setw(16) << "Day" << std::setw(16) << "|Time" << std::setw(21) << "|" + optionHeader << std::setw(19) << "|Instructor" << "|"
       << "\n-------------------------------------------------------------------------\n";
    for (const auto& day : schedule.get()->days) {
        for (const auto& lesson : day.lessons) {
            if (option == 'g' && lesson.groupNumber->getNumber() == groupOrLaneNumber)
            {
                os
                    << std::left << std::setw(16) << day.day
                    << "|" << std::setw(15) << lesson.time
                    << "|" << std::setw(20) << lesson.lane->getLaneNumber()
                    << "|" << std::setw(18) << lesson.instructorName->getLastName() << "|" << "\n";
            }

            else if (option == 'l' && lesson.lane->getLaneNumber() == groupOrLaneNumber)
            {
                os << "Day: " << day.day << "\n"
                   << "Time: " << lesson.time << "\n"
                   << "Group number: " << lesson.groupNumber->getNumber() << "\n"
                   << "Instructor: " << lesson.instructorName->getLastName() << "\n\n";
            }

        }
    }
    os << "=========================================================================\n";
}