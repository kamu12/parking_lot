#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include "CarRecord.cpp"
#include "TimeRecord.cpp"

bool sort_by_time(const TimeRecord &t, const TimeRecord &r)
{
    return t.time < r.time;
}

int main()
{
    std::ifstream in("../data/log.txt");
    std::vector<CarRecord> vect;

    if(in)
    {
        try{
        std::copy(std::istream_iterator<CarRecord>(in),
                  std::istream_iterator<CarRecord>(),
                  std::back_inserter(vect));
        }
        catch(const std::exception& e)
        {
            std::cout << e.what();
        }
    }
    else
    {
        std::cout << "Error open the file" << std::endl;
    }
    
    std::vector<TimeRecord> vect_time_rec;
    for(auto x: vect)
    {
        vect_time_rec.push_back({mktime(&x.time_in.t), true});
        vect_time_rec.push_back({mktime(&x.time_out.t), false});
    }

    std::sort(vect_time_rec.begin(), vect_time_rec.end(), sort_by_time);

    Time busy_start;
    Time busy_end;
    int top_count = 0;
    int count = 0;
    for(auto it = vect_time_rec.begin(); it != vect_time_rec.end(); ++it)
    {
        if(it->drive_in)
        {
            count++;
        }
        else
        {
            if(count > top_count)
            {
                busy_end.t = *localtime(&it->time);
                busy_start.t = *localtime(&std::prev(it)->time);
                top_count = count;
            }
            count --;
        }
    }

    std::cout << "The busiest time was from "<< busy_start << " to " 
    << busy_end << " with car capacity of " << top_count << std::endl;
}