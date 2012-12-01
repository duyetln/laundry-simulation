#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "Event.h"

Event::Event(Type type, unsigned int time, EventHandler* handler)
  : type(type), time(time), handler(handler)
{
}

Event::Event(const Event& e)
  : type(e.type), time(e.time), handler((e.handler)->clone())
{
}

Event& Event::operator=(const Event& e)
{
  type = e.type;
  time = e.time;
  delete handler;
  handler = (e.handler)->clone();
  return *this;
}

Event::~Event()
{
  delete handler;
}

unsigned int Event::getTime() const
{
  return time;
}

Event::Type Event::getType() const
{
  return type;
}

EventHandler& Event::getEventHandler() const
{
  return (*handler);
}

bool operator<(const Event& left, const Event& right)
{
  return left.getTime() < right.getTime(); //left happens before right?
}

bool operator>(const Event& left, const Event& right)
{
  return left.getTime() > right.getTime(); //left happens after right?
}

bool operator==(const Event& left, const Event& right)
{
  return left.getTime() == right.getTime();
}

bool operator!=(const Event& left, const Event& right)
{
  return left.getTime() != right.getTime();
}

bool operator<=(const Event& left, const Event& right)
{
  return left.getTime() <= right.getTime();
}

bool operator>=(const Event& left, const Event& right)
{
  return left.getTime() >= right.getTime();
}

ostream& operator<<(ostream& out, const Event& e)
{
  string type;
  switch(e.getType())
  {
    case Event::Type::GARMENTS_ADDED:
      type = "GARMENTS_ADDED"; break;
    case Event::Type::GARMENTS_RETURNED: 
      type = "GARMENTS_RETURNED"; break;
    case Event::Type::EMPLOYEE_REQUESTED: 
      type = "EMPLOYEE_REQUESTED"; break;
    case Event::Type::EMPLOYEE_BUSY: 
      type = "EMPLOYEE_BUSY"; break;
    case Event::Type::EMPLOYEE_FREE: 
      type = "EMPLOYEE_FREE"; break;
    case Event::Type::PRETREATMENT_START: 
      type = "PRETREATMENT_START"; break;
    case Event::Type::PRETREATMENT_END: 
      type = "PRETREATMENT_END"; break;
    case Event::Type::CLEANING_START: 
      type = "CLEANING_START"; break;
    case Event::Type::CLEANING_END: 
      type = "CLEANING_END"; break;
    case Event::Type::FINISHING_START: 
      type = "FINISHING_START"; break;
    case Event::Type::FINISHING_END: 
      type = "FINISHING_END"; break;
  }
  out << "Event: " << type << " at " << e.getTime();
  return out;
}
