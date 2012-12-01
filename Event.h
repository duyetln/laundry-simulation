#ifndef EVENT_H
#define EVENT_H

#include <iostream>

#include "EventHandler.h"

class Event
{
  public:
    enum Type
    {
      GARMENTS_ADDED,
      GARMENTS_RETURNED,
      EMPLOYEE_REQUESTED,
      EMPLOYEE_BUSY,
      EMPLOYEE_FREE,
      PRETREATMENT_START, //per garment
      PRETREATMENT_END,
      CLEANING_START, //per load of garment/machine
      CLEANING_END,
      FINISHING_START,
      FINISHING_END
    };
  
    Event(Type type, unsigned int time, EventHandler* handler);
    Event(const Event& e);
    Event& operator=(const Event& e);
    ~Event();
    
    unsigned int getTime() const;
    Type getType() const;
    EventHandler& getEventHandler() const;

  private:
    Type type;
    unsigned int time;
    EventHandler* handler;
};

bool operator<(const Event& left, const Event& right);
bool operator>(const Event& left, const Event& right);
bool operator==(const Event& left, const Event& right);
bool operator!=(const Event& left, const Event& right);
bool operator<=(const Event& left, const Event& right);
bool operator>=(const Event& left, const Event& right);
std::ostream& operator<<(std::ostream& out, const Event& e);

#endif //EVENT_H
