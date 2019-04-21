#include "TrainController.hpp"


Train TrainController::getNextTrain(std::string station)
{
    time_t now = time(NULL);
    struct tm now_tm = * localtime(&now);
    return getLastTrainBefore(now_tm.tm_hour, now_tm.tm_min, station);
}


Train TrainController::getLastTrainBefore(int hour, int min, std::string station)
{
    return Train();
}


Train TrainController::getNextTrainFrom(int hour, int min, std::string station)
{
    return Train();
}


std::vector<Train> TrainController::getTodayTrains(std::string station)
{
    std::vector<Train> trains;
    
    
    
    return trains;
}
