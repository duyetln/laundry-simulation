#include <ctime>
#include <random>
using namespace std;

#include "Simulator.h"
#include "Event.h"
#include "PriorityQueue.h"
#include "NormalIntDistribution.h"

void Simulator::resetState(State& state)
{
  state.endTime = 0;
  state.currentTime = 0;
      
  state.pretreatmentQueue = 0;
  state.scheduledPretreatment = 0;
  state.cleaningQueue = 0;
  state.scheduledCleaning = 0;
  state.finishingQueue = 0;
  state.scheduledFinishing = 0;
  state.completeQueue = 0;
            
  state.freeEmployeeNum = 0;
  state.scheduledEmployeeNum = 0;
  state.freePretreatmentStationNum = 0;
  state.scheduledPretreatmentStationNum = 0;
  state.freeCleaningStationNum = 0;
  state.scheduledCleaningStationNum = 0;
  state.freeFinishingStationNum = 0;
  state.scheduledFinishingStationNum = 0;
      
  state.pretreatmentMean = 0;
  state.pretreatmentDev = 0;
      
  state.cleaningDuration = 0;
  state.cleaningMaxLoad = 0;
      
  state.finishingMean = 0;
  state.finishingDev = 0;
      
  state.arrivalMean = 0;
  state.arrivalDev = 0;
      
  state.garmentMean = 0;
  state.garmentDev = 0;
      
  state.loads.clear();    
  state.schedule.emptyQueue();
  
  state.completedLoadNum = 0;
}

unsigned int Simulator::randomNormalInt(double mean, double stddev, unsigned int min, unsigned int max)
{
  mt19937 engine;
  engine.seed((unsigned long)time(NULL));
  
  NormalIntDistribution<unsigned int> distribution(mean, stddev, min, max);

  return distribution(engine);
}

unsigned int Simulator::randomUniformInt(unsigned int min, unsigned int max)
{
  mt19937 engine;
  engine.seed((unsigned long)time(NULL));
  
  uniform_int_distribution<unsigned int> distribution(min, max);
  
  return distribution(engine);
}
