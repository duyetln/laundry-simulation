#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

#include "PriorityQueue.h"

class Event;

class Simulator
{
  public:
    struct CleaningLoad
    {
      unsigned int size;
      unsigned int start;
      unsigned int end;
    };
    
    struct State
    {
      unsigned int duration; //in seconds
      unsigned int currentTime; //in seconds; assuming time starts at 0
      
      unsigned int pretreatmentQueue; //the number of garments waiting to go through the pretreatment stage
      unsigned int scheduledPretreatment; //the number of garments scheduled for pretreatment but not pretreated yet
      unsigned int cleaningQueue; //the number of garments waiting to go through the cleaning stage
      unsigned int scheduledCleaning;
      unsigned int finishingQueue; //the number of garments waiting to go through the finishing stage
      unsigned int scheduledFinishing;
      
      unsigned int completeQueue; //the number of finished garments
            
      unsigned int freeEmployeeNum;
      unsigned int scheduledEmployeeNum;
      unsigned int freePretreatmentStationNum;
      unsigned int scheduledPretreatmentStationNum;
      unsigned int freeCleaningStationNum;
      unsigned int scheduledCleaningStationNum;
      unsigned int freeFinishingStationNum;
      unsigned int scheduledFinishingStationNum;
      
      //time taken to pretreat a garment
      unsigned int pretreatmentMean;
      unsigned int pretreatmentDev;
      
      unsigned int cleaningDuration;
      unsigned int cleaningMaxLoad;
      
      //time taken to finish a garment 
      unsigned int finishingMean;
      unsigned int finishingDev;
      
      //time elapsed between customer arrival; in this case, GARMENTS_ADDED events
      unsigned int arrivalMean;
      unsigned int arrivalDev;
      
      //the number of garments added
      unsigned int garmentMean;
      unsigned int garmentDev;
      
      std::vector<CleaningLoad> loads; //merely to keep tract of which one is running
      PriorityQueue<Event> schedule;
    };
    
    static void resetState(State& state);
    static unsigned int randomNormalInt(double mean, double stddev, unsigned int min, unsigned int max);
    static unsigned int randomUniformInt(unsigned int min, unsigned int max);
    
};

#endif //SIMULATOR_H
