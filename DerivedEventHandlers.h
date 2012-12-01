#ifndef DERIVED_EVENT_HANDLERS_H
#define DERIVED_EVENT_HANDLERS_H

#include <vector>

#include "Simulator.h"
#include "EventHandler.h"

class GarmentsAddedHandler      : public EventHandler
{
  public:
    virtual GarmentsAddedHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class GarmentsReturnedHandler   : public EventHandler
{
  public:
    virtual GarmentsReturnedHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class EmployeeRequestedHandler  : public EventHandler
{
  public:
    virtual EmployeeRequestedHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class EmployeeBusyHandler       : public EventHandler
{
  public:
    virtual EmployeeBusyHandler* clone() const;    
    virtual void execute(Simulator::State& state);
};

class EmployeeFreeHandler       : public EventHandler
{
  public:
    virtual EmployeeFreeHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class PretreatmentStartHandler  : public EventHandler
{
  public:
    virtual PretreatmentStartHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class PretreatmentEndHandler    : public EventHandler
{
  public:
    virtual PretreatmentEndHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class CleaningStartHandler      : public EventHandler
{
  public:
    virtual CleaningStartHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class CleaningEndHandler        : public EventHandler
{
  public:
    virtual CleaningEndHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class FinishingStartHandler     : public EventHandler
{
  public:
    virtual FinishingStartHandler* clone() const;
    virtual void execute(Simulator::State& state);
};

class FinishingEndHandler       : public EventHandler
{
  public:
    virtual FinishingEndHandler* clone() const;
    virtual void execute(Simulator::State& state);
};


#endif //DERIVED_EVENT_HANDLERS_H
