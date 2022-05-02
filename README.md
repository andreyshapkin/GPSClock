# GpsClock
 
This programm takes time from GPS.
It has two displays, one display shows time in local time zone, the other 4 other timezones.

Arduino: Uno or Nano
GPS used: GPS NEO-6M (NMEA 9600)
LCD display used: 1.3" SSH1106 monochrome display

Power:
All devices are powered by 5V provided by arduino (see GND and 5V pins).
On Arduino Uno 3.3V is sufficient, LVR on Arduino Nano makes displays blink (perhaps unit issue).
!!! Make sure GPS supports 5V, most GPS modules have built-in LVR to 3.3V.

Connectivity Display:
Displays connected to I2C. 
First display goes with default address 0x3c.
Second display needs re-soldering of the jumper resistor on the back of display to change address, makes it 0x3d.

Connectivity GPS:
GPS is connected to software serial ports (pins 2-Rx and 3-Tx)
TX of GPS should be connected to pin 2, RX of GPS to pin 3.


