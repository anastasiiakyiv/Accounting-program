#include "Group.h"
#include "Lane.h"
#include "Instructor.h"

class Instructor;
class Lane
{
    int number;

public:
    Lane(int number) : number(number) {}

    int getLaneNumber() const
    {
        return number;
    }
};

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

void printSchedule(const WeeklySchedule& schedule)
{
    std::cout << "============================ Weekly Schedule ============================\n\n";
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << std::setw(16) << std::left << "Time";
    std::cout << std::setw(16) << std::left << "|Lane number";
    std::cout << std::setw(21) << std::left << "|Instructor";
    std::cout << std::setw(15) << std::left << "|Group number" << "    |";
    std::cout << "\n-------------------------------------------------------------------------\n";

    for (const auto& day : schedule.days) {
        std::cout << std::setw(10) << std::left << day.day 
            << "                                                              |";
        std::cout << "\n-------------------------------------------------------------------------";

        if (day.lessons.empty()) {
            std::cout << std::setw(15) << std::left << "No lessons for this day.";
            std::cout << "\n-------------------------------------------------------------------------\n";
        }
        else {
            for (const auto& lesson : day.lessons) {
                std::cout << std::endl;
                std::cout << "|" << std::setw(15) << std::left << lesson.time;
                std::cout << "|" << std::setw(15) << std::left << lesson.lane->getLaneNumber();
                std::cout << "|" << std::setw(20) << std::left << lesson.instructorName->getLastName();
                std::cout << "|" << std::setw(15) << std::left << lesson.groupNumber->getNumber() << "\t|";
            }
            std::cout << "\n";
            std::cout << "-------------------------------------------------------------------------\n";
        }
    }
}
