
const char* GPS_WEEKDAY[] = {"", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//enum month_t {Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

class GPSDisplayMain {
  private:
    GPSDisplayContainer display_dev;
    uint16_t i2c_addr;
    bool clear_display = true;
    bool is_gps_lost = false;
    uint8_t last_min = 0xff;
    uint8_t last_sec_chunk = 0xff;
  public:
    GPSDisplayMain(uint16_t _i2c_addr) {
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
      GPSTime& time_pdx = getLocalTime(timezonPDX, time_utc);

      is_gps_lost = false;

      if (clear_display) {
        clear_display = false;
        last_min = 0xff;
        display.clear();
      }

      // only refresh when minute changes, otherwise nothing to refresh
      if (last_min != time_pdx.minute) {
        last_min = time_pdx.minute;

        display.setFont(X11fixed7x14);
        display.setCursor(35, 0);
        display.println("PDX TIME");

        display.setFont(lcdnums14x24);
        display.setCursor(25, 2);
        sprintf(buffer, "%02d:%02d", time_pdx.hour, time_pdx.minute);
        display.print(buffer);

        display.setFont(X11fixed7x14);
        display.setCursor(0, 6);
        sprintf(buffer, "%02d/%02d/%02d %s ww%02d", time_pdx.month, time_pdx.day, time_pdx.year % 100, GPS_WEEKDAY[time_pdx.weekday], getWorkWeek(time_pdx));
        display.println(buffer);
      }

      uint8_t sec_chunk = time_pdx.second / 3;
      if (last_sec_chunk != sec_chunk) {
        last_sec_chunk = sec_chunk;
        sprintf(buffer, "");
        for (uint8_t i = 0; i < 20; i++) {
          if (i <= sec_chunk) {
            sprintf(buffer + strlen(buffer), "_");
          } else {
            sprintf(buffer + strlen(buffer), " ");
          }
        }
        display.setFont(lcd5x7);
        display.setCursor(0, 5);
        display.println(buffer);
      }
    }


    void gps_lost() {
      char* buffer = get_buf();
      GPSDisplay& display = display_dev.get_display();

      if (!is_gps_lost) {
        display.setFont(X11fixed7x14);
        display.setCursor(10, 0);
        display.println("*** GPS LOST ***");
      }
      is_gps_lost = true;
      clear_display = true;
    }

};
