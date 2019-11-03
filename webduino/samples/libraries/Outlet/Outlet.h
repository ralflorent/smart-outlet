/*
  Outlet.h - Component object representing an outlet.
  Author: Ralph Florent 
  Created on Oct 29, 2016
*/
#ifndef Outlet_h
#define Outlet_h

#include "Arduino.h"

class Outlet
{
  public:
    Outlet();
    Outlet(char, boolean);

    void setId(char);
    void setState(boolean);
    void setScheduled(String);
    void setDescription(String);

    char getId();
    boolean getState();
    String getScheduled();
    String getDescription();

    void begin();
	void turnOn();
    void turnOff();

  private:
    char _id;
    boolean _state;
    String _description;
    String _scheduled;
};

#endif
