#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#include "GPSCommon.h"

// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);


class GPSDevice {
private:
  GPSTime time;
  uint8_t last_second = 0;
  bool time_changed = false;
  bool time_valid = false;
  
public:
  GPSDevice() {}

  void setup() {
    gpsSerial.begin(GPSBaud);
  }

  void step() {
    if (gpsSerial.available()==0) {
      return;
    }
    
    // read GPS data if any
    bool message_received = false;
    while (gpsSerial.available() && !message_received) {
      message_received = message_received || gps.encode(gpsSerial.read());
    }

    // still haven't locked on time
    if (!gps.date.isValid() || !gps.time.isValid()) {
      return;
    }

    time.set_date(gps.date.year(), gps.date.month(), gps.date.day(), 0);
    time.set_time(gps.time.hour(), gps.time.minute(), gps.time.second());

    //sprintf(get_buf(),"DEBUG: %s", time.str());
    //Serial.println(get_buf());

    // if time isn't initialized year is printed as 2000, while the valid flag is set, GPS bug-feature????
    if (time.year <= 2000) {
      time_valid = false;
      return;
    }

    time_valid = true;

    if (last_second != time.second) {
      last_second = time.second;
      time_changed = true;
    }
  }
  
  bool is_time_changed() {
    bool result = time_changed;
    time_changed = false;
    return result;
  }
  
  bool is_time_valid() {
    return time_valid;
  }

  GPSTime& get_time() {
    return time;
  }
};
