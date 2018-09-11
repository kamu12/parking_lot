#pragma once
#include <iostream>
#include"Time.cpp"

class CarRecord
{
    public:
        Time time_in;
        Time time_out;

        CarRecord():time_in(Time()), time_out(Time()){}
        CarRecord(Time in, Time out):time_in(in), time_out(out){}



        friend std::istream &operator>>(std::istream &, CarRecord &);
        friend std::ostream &operator<<(std::ostream &, const CarRecord &);
};


std::istream &operator>>(std::istream &in, CarRecord &record)
{
    in >> record.time_in >> record.time_out;
    return in;
}

std::ostream &operator<<(std::ostream &out, const CarRecord &record)
{
    out << record.time_in << " " << record.time_out;
    return out;
}