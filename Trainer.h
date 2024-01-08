#pragma once
#include <iostream>
#include <vector>
#include "Lesson.h"

class Trainer
{
    std::string lastName;
    std::string phoneNumber;
    double hourlyRate;
    std::vector<Lesson> schedule;

public:
    Trainer(const std::string& last, const std::string& phone, double rate)
        : lastName(last), phoneNumber(phone), hourlyRate(rate) {}

    std::string getLastName() const 
    {
        return lastName;
    }

    std::string getPhoneNumber() const 
    {
        return phoneNumber;
    }

    double getHourlyRate() const 
    {
        return hourlyRate;
    }

    std::vector<Lesson> getSchedule() const 
    {
        return schedule;
    }

    void setLastName(const std::string& last) 
    {
        lastName = last;
    }

    void setPhoneNumber(const std::string& phone) 
    {
        phoneNumber = phone;
    }

    void setHourlyRate(double rate) 
    {
        hourlyRate = rate;
    }

    void setSchedule(const std::vector<Lesson>& newSchedule) 
    {
        schedule = newSchedule;
    }
};