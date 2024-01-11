#pragma once
#include <vector>
#include <memory>
#include "Lesson.h"

class Lane
{
    int number;
    std::vector<std::shared_ptr<Lesson>> schedule;

public:
    Lane(int number) : number(number) { }

    std::vector<std::shared_ptr<Lesson>> getSchedule() const 
    {
        return schedule;
    }
    void addLessonToSchedule(std::shared_ptr<Lesson> lesson)
    {
        schedule.push_back(lesson);
    }
};