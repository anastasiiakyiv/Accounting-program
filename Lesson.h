#pragma once
#include "Group.h"

class Lesson
{
    std::string time;
    std::string dayOfWeek;
    int laneNumber;
    int groupNumber;

public:
    Lesson(const std::string& lessonTime, int track, const std::string& day, const int groupNumber)
        : time(lessonTime), laneNumber(track), dayOfWeek(day), Group(groupNumber) {}

    std::string getTime() const 
    {
        return time;
    }

    int getLaneNumber() const 
    {
        return LaneNumber;
    }

    std::string getDayOfWeek() const 
    {
        return dayOfWeek;
    }
};
