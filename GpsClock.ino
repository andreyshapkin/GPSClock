#include <avr/wdt.h>
#include "GPSDevice.h"
#include "GPSTimeConverter.h"
#include "GPSDisplayASCII.h"
#include "GPSDisplayMain.h"
#include "GPSDisplaySecond.h"
#include "GPSTimer.h"

GPSDevice gpsDevice;
GPSDisplayMain display_main(0x3c);
GPSDisplaySecond display_second(0x3d);
GPSTimerMS timer_ms(30000);

void setup() {
  //Serial.begin(9600);
  //Serial.println(F("Initializing watchdog"));
  wdt_enable(WDTO_8S);
  //Serial.println(F("Initializing GPS"));
  gpsDevice.setup();
  //Serial.println(F("Initializing Displays"));
  display_main.setup();
  display_second.setup();
}

void loop() {
  // reset watchdog
  wdt_reset();

  gpsDevice.step();

  if (gpsDevice.is_time_valid() && gpsDevice.is_time_changed()) {
    timer_ms.reset();
    GPSTime& time_utc = gpsDevice.get_time();
    display_main.update(time_utc);
    display_second.update(time_utc);
  }

  if (timer_ms.fired()) {
    display_main.gps_lost();
  }

}
