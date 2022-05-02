

class GPSDisplaySecond {
  private:
    GPSDisplayContainer display_dev;
    uint16_t i2c_addr;
    bool first_time = true;
  public:
    GPSDisplaySecond(uint16_t _i2c_addr) {
      i2c_addr = _i2c_addr;
    }

    void setup() {
      display_dev.setup(i2c_addr);

      GPSDisplay& display = display_dev.get_display();
      display.setFont(X11fixed7x14);
      display.setCursor(0, 2);
      display.println("Waiting for GPS");
    }

    void update(GPSTime& time_utc) {
      char* buffer = get_buf();
      GPSDisplay& display = display_dev.get_display();
      if (first_time) {
        first_time = false;
        display.clear();
      }

      GPSTime& time = getLocalTime(timezonMY, time_utc);

      display.setFont(X11fixed7x14);
      display.setCursor(0, 0);
      display.println("Malaysia");

      display.setFont(lcdnums12x16);
      display.setCursor(0, 2);
      sprintf(buffer, "%02d:%02d", time.hour, time.minute);
      display.print(buffer);

      time = getLocalTime(timezonIND, time_utc);

      display.setFont(X11fixed7x14);
      display.setCursor(68, 0);
      display.println("India");

      display.setFont(lcdnums12x16);
      display.setCursor(68, 2);
      sprintf(buffer, "%02d:%02d", time.hour, time.minute);
      display.print(buffer);

      time = getLocalTime(timezonIDC, time_utc);

      display.setFont(X11fixed7x14);
      display.setCursor(0, 4);
      display.println("Israel");

      display.setFont(lcdnums12x16);
      display.setCursor(0, 6);
      sprintf(buffer, "%02d:%02d", time.hour, time.minute);
      display.print(buffer);

      time = getLocalTime(timezonMOW, time_utc);

      display.setFont(X11fixed7x14);
      display.setCursor(68, 4);
      display.println("Moscow");

      display.setFont(lcdnums12x16);
      display.setCursor(68, 6);
      sprintf(buffer, "%02d:%02d", time.hour, time.minute);
      display.print(buffer);

    }
};
