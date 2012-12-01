#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "Simulator.h"
#include "PriorityQueue.h"
#include "Event.h"
#include "DerivedEventHandlers.h"

int main()
{
  Simulator::State state;
  Simulator::resetState(state);
  
  unsigned int simulationDuration; //in hours;
  cin >> simulationDuration;
  state.endTime = 0 + simulationDuration * 3600; //input is in hours while the default is seconds
  state.currentTime = 0;
  
  cin >> state.freeEmployeeNum;
  cin >> state.freePretreatmentStationNum;
  cin >> state.freeCleaningStationNum;
  cin >> state.freeFinishingStationNum;
  cin >> state.pretreatmentMean >> state.pretreatmentDev;
  cin >> state.cleaningDuration >> state.cleaningMaxLoad;
  cin >> state.finishingMean >> state.finishingDev;
  cin >> state.arrivalMean >> state.arrivalDev;
  cin >> state.garmentMean >> state.garmentDev;
  
  Event garmentsAdded(Event::Type::GARMENTS_ADDED, state.currentTime, new GarmentsAddedHandler);
  state.schedule.enqueue(garmentsAdded);
  
  while(state.schedule.size() > 0 && state.currentTime <= state.endTime)
  { 
    Event event = *(state.schedule.getLowest());
    state.currentTime = event.getTime();
    if (state.currentTime <= state.endTime)
    {
      cout << event << endl;
      state.schedule.dequeueLowest();
      event.getEventHandler().execute(state);
    }
  }
  
  cout << endl;
  cout << "---------------------------------------------------------------------------------------------------" << endl;
  cout << "Statistics:" << endl;
  cout << "Completely processed: " << state.completeQueue << endl;
  cout << "Being processed: " << state.pretreatmentQueue + state.cleaningQueue + state.finishingQueue << endl;
  cout << "Complete batches: " << state.completedLoadNum << endl;
  cout << "Idle time percentage: " << "Forgot about this part until it is too late to add to the program... :(" << endl;

  return 0;
}
