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
  
  state.pretreatmentQueue = 7;
  state.freeEmployeeNum = 3;
  state.freePretreatmentStationNum = 3;
  state.freeCleaningStationNum = 2;
  state.freeFinishingStationNum = 4;
  
  state.pretreatmentMean = 5;
  state.pretreatmentDev = 0;
  state.cleaningDuration = 10;
  state.cleaningMaxLoad = 3;
  state.finishingMean = 3;
  state.finishingDev = 0;
  
  state.garmentMean = 4;
  state.garmentDev = 1;
  
  Event employeeRequested(Event::Type::EMPLOYEE_REQUESTED, 0, new EmployeeRequestedHandler);
  state.schedule.enqueue(employeeRequested);
  
  unsigned int times = 0;
  while( state.schedule.size() > 0)
  { 
    cout << "loop " << times << endl;
    Event event = *(state.schedule.getLowest());
    state.schedule.dequeueLowest();
    state.currentTime = event.getTime();
    cout << "Current time: " << state.currentTime << endl;
    cout << event << endl;
    if (times == 50)
    {
      Event garmentsAdded(Event::Type::GARMENTS_ADDED, state.currentTime, new GarmentsAddedHandler);
      state.schedule.enqueue(garmentsAdded);
    }
    event.getEventHandler().execute(state);
    cout << endl;
    times++;
  }
  
  cout << "Schedule" << endl;
  cout << state.scheduledPretreatment << endl;
  cout << state.scheduledCleaning << endl;
  cout << state.scheduledFinishing << endl;
  cout << state.scheduledEmployeeNum << endl;
  cout << state.scheduledPretreatmentStationNum << endl;
  cout << state.scheduledCleaningStationNum << endl;
  cout << state.scheduledFinishingStationNum << endl;
  cout << "Queue" << endl;
  cout << state.pretreatmentQueue << endl;
  cout << state.cleaningQueue << endl;
  cout << state.finishingQueue << endl;
  cout << state.completeQueue << endl;
  cout << "Num" << endl;
  cout << state.freeEmployeeNum << endl;
  cout << state.freePretreatmentStationNum << endl;
  cout << state.freeCleaningStationNum << endl;
  cout << state.freeFinishingStationNum << endl;

  return 0;
}
