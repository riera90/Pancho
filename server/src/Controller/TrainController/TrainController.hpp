#ifndef _PANCHO_TRAIN_CONTROLLER
#define _PANCHO_TRAIN_CONTROLLER

#include <time.h>
#include <string>
#include <vector>
#include "Train.cpp"

namespace TrainController
{
    Train getNextTrain(std::string station);
    Train getLastTrainBefore(int hour, int minute, std::string station);
    Train getNextTrainFrom(int hour, int minute, std::string station);
    std::vector<Train> getTodayTrains(std::string station);
}

#endif