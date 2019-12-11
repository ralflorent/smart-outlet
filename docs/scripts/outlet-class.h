#ifndef Outlet_h
#define Outlet_h

class Outlet {
  public:
    // constructors
    Outlet();
    Outlet(char, boolean);

    // setters
    void setId(char);
    void setState(boolean);

    // getters
    char getId();
    boolean getState();

    // methods
    void begin();   // initialize arduino setup
    void turnOn();  // actuates a digital switch from 0 (off) to 1 (on)
    void turnOff(); // actuates a digital switch from 1 (on) to 0 (off)

  private:
    char _id;
    boolean _state;
};

#endif