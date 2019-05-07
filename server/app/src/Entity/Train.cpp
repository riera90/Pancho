#include <pancho/Entity/Train.hpp>


Train::Train (int weekDay,
              int hour,
              int minute,
              const std::string& origin,
              const std::string& destiny)
{
    this->weekDay_ = weekDay;
    this->hour_ = hour;
    this->minute_ = minute;
    this->origin_ = origin;
    this->destiny_ = destiny;
}

int Train::getHour()
{
    return this->hour_;
}

int Train::getMinute()
{
    return this->minute_;
}

int Train::getWeekDay()
{
    return this->weekDay_;
}

const std::string& Train::getOrigin()
{
    return this->origin_;
}

const std::string& Train::getDestiny()
{
    return this->destiny_;
}

bool Train::operator>(Train train)
{
    if (this->hour_ > train.getHour())
        return true;

    return this->hour_ == train.getHour() && this->minute_ > train.getMinute();
}

bool Train::operator>(Alarm alarm)
{
    if (this->hour_ > alarm.getHour())
        return true;

    return this->hour_ == alarm.getHour() && this->minute_ > alarm.getMinute();
}

bool Train::operator<(Train train)
{
    if (this->hour_ < train.getHour())
        return true;

    return this->hour_ == train.getHour() && this->minute_ < train.getMinute();
}

bool Train::operator<(Alarm alarm)
{
    if (this->hour_ < alarm.getHour())
        return true;

    return this->hour_ == alarm.getHour() && this->minute_ < alarm.getMinute();
}