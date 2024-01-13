#pragma once
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