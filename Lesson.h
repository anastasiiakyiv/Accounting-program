#pragma once

class Lesson
{
    std::string time;
    std::string dayOfWeek;
    int trackNumber;

public:
    Lesson(const std::string& lessonTime, int track, const std::string& day)
        : time(lessonTime), trackNumber(track), dayOfWeek(day) {}

    std::string getTime() const
    {
        return time;
    }

    int getTrackNumber() const
    {
        return trackNumber;
    }

    std::string getDayOfWeek() const
    {
        return dayOfWeek;
    }
};