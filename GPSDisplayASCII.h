// https://github.com/greiman/SSD1306Ascii

#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"


typedef SSD1306AsciiAvrI2c GPSDisplay;

#define I2C_FREQ 100000

// 0X3C+SA0 - 0x3C or 0x3D
//#define I2C_ADDRESS 0x3c

class GPSDisplayContainer {
private:
  GPSDisplay display;
public:
  GPSDisplayContainer() {}
  
  void setup(uint32_t i2c_addr) {
    //display.begin(&Adafruit128x64, i2c_addr);
    display.begin(&SH1106_128x64, i2c_addr);
    display.setI2cClock(I2C_FREQ);
    display.clear();    
  }

  GPSDisplay& get_display() {
    return display;
  }
};
