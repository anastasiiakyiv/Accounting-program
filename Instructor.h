#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Lesson;

class Instructor
{
    std::string lastName;
    std::string phoneNumber;
    double hourlyRate;
    std::vector<std::shared_ptr<Lesson>> schedule;

public:


    Instructor(const std::string& last, const std::string& phone, double rate)
        : lastName(last), phoneNumber(phone), hourlyRate(rate) {

    }

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
};
