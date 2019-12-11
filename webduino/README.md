# Webduino

This is a low-level, modular circuitry formed by an Arduino board and a network of sensors.  The Arduino board, a microcontroller, acts as a supervisor of microtasks.  Being the core component of the hardware systems, it controls the different input/output functions of the connected chips.

### Modules
The modules used for the `webduino` as the Smart Outlet prototype are:
* Arduino board (Mega 2560 Rev3)
* Relay module (Elegoo 4-Channel)
* Wi-Fi module (Espressif ESP8266EX)

The specifications as well as the modules interconnection are described in the technical documentation.

### Notes:
For Unix-based systems, Linux in particular, allow permissions on the port with this command:
```bash
sudo chmod a+rw /dev/ttyACM0|USB0
```