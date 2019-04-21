#ifndef _PANCHO_ALARM_CONTROLLER_
#define _PANCHO_ALARM_CONTROLLER_

#include <ctime>
#include "shared.hpp"
#include "Alarm.hpp"

namespace AlarmController
{
    Alarm getNextAlarm();
    Alarm getNextAlarm(tm time);
    Alarm getNextAlarm(time_t time);
}

#endif