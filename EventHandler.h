#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Simulator.h"

class EventHandler
{
  public:
    virtual ~EventHandler(){}
    virtual void execute(Simulator::State &state) = 0; 
    virtual EventHandler* clone() const = 0;
};


#endif //EVENT_HANDLER_H
