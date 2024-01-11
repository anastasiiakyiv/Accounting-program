#pragma once
#include "Group.h"

class Lesson
{
    std::string time;
    std::string dayOfWeek;
    int laneNumber;
    int groupNumber;

public:
    Lesson(const std::string& lessonTime, int laneNumber, const std::string& day, const int groupNumber)
        : time(lessonTime), laneNumber(laneNumber), dayOfWeek(day), groupNumber(groupNumber) {}

    std::string getTime() const 
    {
        return time;
    }

    int getLaneNumber() const 
    {
        return laneNumber;
    }

    std::string getDayOfWeek() const 
    {
        return dayOfWeek;
    }
};
