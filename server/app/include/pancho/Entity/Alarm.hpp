#ifndef _PANCHO_ALARM_
#define _PANCHO_ALARM_

#include <string>

#include <pancho/Entity/Train.hpp>

class Alarm {
private:
    int hour_;
    int minute_;
    int weekDay_;
    std::string description_;

public:
    Alarm (int weekDay, int hour, int minute, std::string description);

    int getHour();
    int getMinute();
    int getWeekDay();
    std::string getDescription();


    bool operator>(Alarm alarm);
    bool operator>(Train train);
    bool operator<(Alarm alarm);
    bool operator<(Train train);
};


#endif