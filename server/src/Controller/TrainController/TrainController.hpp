#ifndef _PANCHO_TRAIN_CONTROLLER
#define _PANCHO_TRAIN_CONTROLLER

#include <ctime>
#include "Train.cpp"

namespace TrainController
{
    Train getNextTrain();
    Train getLastTrainBefore(time_t time);
    Train getLastTrainBefore(tm time);
    Train getNextTrainFrom(time_t time);
    Train getNextTrainFrom(tm time);
}

#endif