#pragma once
#include <iostream>
#include <stdexcept>
#include <ctime>

class Time
{
    public:
        tm t;

        Time()
        {
            t = {};
        }
        Time(int h, int m)
        {   
            t = {0, m, h};
        }
        Time(time_t time)
        {
            t = *localtime(&time);
        }

        friend std::istream &operator>>(std::istream &, Time &);
        friend std::ostream &operator<<(std::ostream &, const Time &);
};

std::istream& colon(std::istream& in)
{
    if ((in >> std::ws).peek() != std::char_traits<char>::to_int_type(':'))
    {
        in.setstate(std::ios_base::failbit);
    }
    return in.ignore();
}
std::istream &operator>>(std::istream &in, Time &t)
{
    int h;
    int m;
    in >> h >> colon >> m;
    t = Time(h, m);
    return in;
}

std::ostream &operator<<(std::ostream &out, const Time &t)
{
    char buffer[20];
    strftime(buffer, 20, "%R", &t.t);
    out << buffer;
    return out;
}
