#ifndef _PANCHO_TRAIN_
#define _PANCHO_TRAIN_

#include <string>
#include <pancho/Entity/Alarm.hpp>

class Train {
private:
    int hour_;
    int minute_;
    int weekDay_;
    std::string origin_;
    std::string destiny_;

public:
    Train (int weekDay, int hour, int minute, const std::string& origin, const std::string& destiny);

    int getHour();
    int getMinute();
    int getWeekDay();
    const std::string& getOrigin();
    const std::string& getDestiny();

    bool operator>(Train train);
    bool operator>(Alarm alarm);
    bool operator<(Train train);
    bool operator<(Alarm alarm);

};


#endif