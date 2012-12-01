#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#include "Simulator.h"
#include "DerivedEventHandlers.h"
#include "Event.h"

//GARMENTS_ADDED
GarmentsAddedHandler* GarmentsAddedHandler::clone() const
{
  return new GarmentsAddedHandler(*this);
}

void GarmentsAddedHandler::execute(Simulator::State& state)
{
  state.pretreatmentQueue += Simulator::randomNormalInt((double)state.garmentMean, (double)state.garmentDev, 1, 100);
    
  Event employeeRequested(Event::Type::EMPLOYEE_REQUESTED, state.currentTime, new EmployeeRequestedHandler);
  state.schedule.enqueue(employeeRequested);
}

//GARMENTS_RETURNED
GarmentsReturnedHandler* GarmentsReturnedHandler::clone() const
{
  return new GarmentsReturnedHandler(*this);
}

void GarmentsReturnedHandler::execute(Simulator::State& state)
{
  //INTENTIONALLY DO NOTHING
}
    
//EMPLOYEE_REQUESTED
EmployeeRequestedHandler* EmployeeRequestedHandler::clone() const
{
  return new EmployeeRequestedHandler(*this);
}

void EmployeeRequestedHandler::execute(Simulator::State& state)
{
  if (state.loads.size() > 0 && state.freeEmployeeNum-state.scheduledEmployeeNum > 0)
  {
    vector<Simulator::CleaningLoad> newLoads; //after removing finished loads
    for (unsigned int i = 0; i < state.loads.size(); i++)
    {
      if (state.loads.at(i).end <= state.currentTime) //this load is done
      {
        state.finishingQueue += state.loads.at(i).size;
      }
      else
      {
        newLoads.push_back(state.loads.at(i));
      }
    }
    state.loads = newLoads;
  }

  unsigned int smallest;
  
  cout << "freeEmployeeNum " << state.freeEmployeeNum << endl;
  cout << "scheduledEmployeeNum " << state.scheduledEmployeeNum << endl << endl;
  
  cout << "finishingQueue " << state.finishingQueue << endl;
  cout << "scheduledFinishing " << state.scheduledFinishing << endl;
  cout << "freeFinishingStationNum " << state.freeFinishingStationNum << endl;
  cout << "scheduledFinishingStationNum " << state.scheduledFinishingStationNum << endl;
  cout << endl;
  
  if (state.finishingQueue-state.scheduledFinishing > 0 
      && state.freeEmployeeNum-state.scheduledEmployeeNum > 0 
      && state.freeFinishingStationNum-state.scheduledFinishingStationNum > 0)
  {
    smallest = min(min(state.finishingQueue-state.scheduledFinishing, 
              state.freeFinishingStationNum-state.scheduledFinishingStationNum), 
              state.freeEmployeeNum-state.scheduledEmployeeNum);
              
    for (unsigned int i = 0; i < smallest; i++)
    {
      Event finishingStart(Event::Type::FINISHING_START, state.currentTime, new FinishingStartHandler);
      state.schedule.enqueue(finishingStart);
      
      Event employeeBusy(Event::Type::EMPLOYEE_BUSY, state.currentTime, new EmployeeBusyHandler);
      state.schedule.enqueue(employeeBusy);
    }
    
    state.scheduledEmployeeNum += smallest;
    state.scheduledFinishing += smallest;
    state.scheduledFinishingStationNum += smallest;
  }
  
  cout << "freeEmployeeNum " << state.freeEmployeeNum << endl;
  cout << "scheduledEmployeeNum " << state.scheduledEmployeeNum << endl << endl;
  
  cout << "cleaningQueue " << state.cleaningQueue << endl;
  cout << "scheduledCleaning " << state.scheduledCleaning << endl;
  cout << "freeCleaningStationNum " << state.freeCleaningStationNum << endl;
  cout << "scheduledCleaningStationNum " << state.scheduledCleaningStationNum << endl;
  cout << endl;
  
  if (state.cleaningQueue-state.scheduledCleaning > 0 
      && state.freeEmployeeNum-state.scheduledEmployeeNum > 0 
      && state.freeCleaningStationNum-state.scheduledCleaningStationNum > 0 
      && (state.cleaningQueue-state.scheduledCleaning > state.cleaningMaxLoad 
      || state.pretreatmentQueue == 0))
  {
    smallest = min(state.freeCleaningStationNum-state.scheduledCleaningStationNum, 
    (unsigned int)((state.cleaningQueue-state.scheduledCleaning)/state.cleaningMaxLoad <= 0 ? 1 : (state.cleaningQueue-state.scheduledCleaning)/state.cleaningMaxLoad));
    cout << smallest << endl;
    
    Event employeeFree(Event::Type::EMPLOYEE_FREE, state.currentTime, new EmployeeFreeHandler);
    state.schedule.enqueue(employeeFree);

    for (unsigned int i = 0; i < smallest; i++)
    {
      Event cleaningStart(Event::Type::CLEANING_START, state.currentTime, new CleaningStartHandler);
      state.schedule.enqueue(cleaningStart);
    }
    
    Event employeeBusy(Event::Type::EMPLOYEE_BUSY, state.currentTime, new EmployeeBusyHandler);
    state.schedule.enqueue(employeeBusy);
    
    state.scheduledEmployeeNum++;
    state.scheduledCleaning += (smallest > 1 ? smallest*state.cleaningMaxLoad : (state.cleaningQueue-state.scheduledCleaning < state.cleaningMaxLoad ? state.cleaningQueue-state.scheduledCleaning : state.cleaningMaxLoad));
    state.scheduledCleaningStationNum += smallest;
  }
  
  cout << "freeEmployeeNum " << state.freeEmployeeNum << endl;
  cout << "scheduledEmployeeNum " << state.scheduledEmployeeNum << endl << endl;
  
  cout << "pretreatmentQueue " << state.pretreatmentQueue << endl;
  cout << "scheduledPretreatment " << state.scheduledPretreatment << endl;
  cout << "freePretreatmentStationNum " << state.freePretreatmentStationNum << endl;
  cout << "scheduledPretreatmentStationNum " << state.scheduledPretreatmentStationNum << endl;
  cout << endl;
  
  if (state.pretreatmentQueue-state.scheduledPretreatment > 0 
      && state.freeEmployeeNum-state.scheduledEmployeeNum > 0 
      && state.freePretreatmentStationNum-state.scheduledPretreatmentStationNum > 0)
  {
    smallest = min(min(state.pretreatmentQueue-state.scheduledPretreatment, 
              state.freePretreatmentStationNum-state.scheduledPretreatmentStationNum), 
              state.freeEmployeeNum-state.scheduledEmployeeNum);
              
    for (unsigned int i = 0; i < smallest; i++)
    {
      Event pretreatmentStart(Event::Type::PRETREATMENT_START, state.currentTime, new PretreatmentStartHandler);
      state.schedule.enqueue(pretreatmentStart);
    
      Event employeeBusy(Event::Type::EMPLOYEE_BUSY, state.currentTime, new EmployeeBusyHandler);
      state.schedule.enqueue(employeeBusy);
    }
    
    state.scheduledEmployeeNum += smallest;
    state.scheduledPretreatment += smallest;
    state.scheduledPretreatmentStationNum += smallest;
  }
  
  cout << "freeEmployeeNum " << state.freeEmployeeNum << endl;
  cout << "scheduledEmployeeNum " << state.scheduledEmployeeNum << endl << endl;
  
}

//EMPLOYEE_BUSY    
EmployeeBusyHandler* EmployeeBusyHandler::clone() const
{
  return new EmployeeBusyHandler(*this);
}

void EmployeeBusyHandler::execute(Simulator::State& state)
{
  state.freeEmployeeNum--;
  state.scheduledEmployeeNum--;
  cout << "freeEmployeeNum " << state.freeEmployeeNum << endl;
  cout << "scheduledEmployeeNum " << state.scheduledEmployeeNum << endl;
}


//EMPLOYEE_FREE    
EmployeeFreeHandler* EmployeeFreeHandler::clone() const
{
  return new EmployeeFreeHandler(*this);
}

void EmployeeFreeHandler::execute(Simulator::State& state)
{
  state.freeEmployeeNum++;
  
  cout << "freeEmployeeNum " << state.freeEmployeeNum << endl;
  cout << "scheduledEmployeeNum " << state.scheduledEmployeeNum << endl;
  
  //abusive boss doesn't let the employees have a break
  Event employeeRequested(Event::Type::EMPLOYEE_REQUESTED, state.currentTime, new EmployeeRequestedHandler);
  state.schedule.enqueue(employeeRequested);
}

//PRETREATMENT_START 
PretreatmentStartHandler* PretreatmentStartHandler::clone() const
{
  return new PretreatmentStartHandler(*this);
}

void PretreatmentStartHandler::execute(Simulator::State& state)
{
  state.pretreatmentQueue--;
  state.scheduledPretreatment--;
  state.freePretreatmentStationNum--;
  state.scheduledPretreatmentStationNum--;
  
  Event pretreatmentEnd(Event::Type::PRETREATMENT_END, state.currentTime + Simulator::randomNormalInt(state.pretreatmentMean, state.pretreatmentDev, 1, (unsigned int)pow(2,31)), new PretreatmentEndHandler);
  state.schedule.enqueue(pretreatmentEnd);
}

//PRETREATMENT_END    
PretreatmentEndHandler* PretreatmentEndHandler::clone() const
{
  return new PretreatmentEndHandler(*this);
}

void PretreatmentEndHandler::execute(Simulator::State& state)
{
  state.freePretreatmentStationNum++;
  state.cleaningQueue++;
  
  Event employeeFree(Event::Type::EMPLOYEE_FREE, state.currentTime, new EmployeeFreeHandler);
  state.schedule.enqueue(employeeFree);
}

//CLEANING_START
CleaningStartHandler* CleaningStartHandler::clone() const
{
  return new CleaningStartHandler(*this);
}

void CleaningStartHandler::execute(Simulator::State& state)
{
  unsigned int size = (state.cleaningQueue < state.cleaningMaxLoad ? state.cleaningQueue : state.cleaningMaxLoad);
  
  state.cleaningQueue -= size;
  state.scheduledCleaning -= size;
  state.freeCleaningStationNum--;
  state.scheduledCleaningStationNum--;
  
  unsigned int start = state.currentTime;
  unsigned int end = state.currentTime + state.cleaningDuration;
  
  Simulator::CleaningLoad load;
  load.size = size;
  load.start = start;
  load.end = end;
  
  state.loads.push_back(load);
  
  Event cleaningEnd(Event::Type::CLEANING_END, end, new CleaningEndHandler);
  state.schedule.enqueue(cleaningEnd);
}
    
CleaningEndHandler* CleaningEndHandler::clone() const
{
  return new CleaningEndHandler(*this);
}

//CLEANING_END
void CleaningEndHandler::execute(Simulator::State& state)
{
  state.freeCleaningStationNum++;
  
  Event employeeRequested(Event::Type::EMPLOYEE_REQUESTED, state.currentTime, new EmployeeRequestedHandler);
  state.schedule.enqueue(employeeRequested);
}

//FINISHING_START    
FinishingStartHandler* FinishingStartHandler::clone() const
{
  return new FinishingStartHandler(*this);
}

void FinishingStartHandler::execute(Simulator::State& state)
{
  state.finishingQueue--;
  state.scheduledFinishing--;
  state.freeFinishingStationNum--;
  state.scheduledFinishingStationNum--;
  
  Event finishingEnd(Event::Type::FINISHING_END, state.currentTime + Simulator::randomNormalInt(state.finishingMean, state.finishingDev, 1, (unsigned)pow(2,31)), new FinishingEndHandler);
  state.schedule.enqueue(finishingEnd);
}

//FINISHING_END    
FinishingEndHandler* FinishingEndHandler::clone() const
{
  return new FinishingEndHandler(*this);
}

void FinishingEndHandler::execute(Simulator::State& state)
{
  state.freeFinishingStationNum++;
  state.completeQueue++;
  
  Event garmentsReturned(Event::Type::GARMENTS_RETURNED, state.currentTime, new GarmentsReturnedHandler);
  state.schedule.enqueue(garmentsReturned);
  
  Event employeeFree(Event::Type::EMPLOYEE_FREE, state.currentTime, new EmployeeFreeHandler);
  state.schedule.enqueue(employeeFree);

}
    
    
    
    
    
