
#ifndef DEF_GPSCOMMON
#define DEF_GPSCOMMON

char _str[100];

char* get_buf() {
  return _str;
}

char __time_str[60];

class GPSTime {
  public:
    uint16_t year=0;
    uint8_t month=0;
    uint8_t day=0;
    uint8_t hour=0;
    uint8_t minute=0;
    uint8_t second=0;
    uint8_t weekday=0;

    char* str() {
      sprintf(__time_str,"%02d:%02d:%02d %02d/%02d/%04d (%d)", hour, minute, second, month, day, year, weekday);
      return __time_str;
    }

    void set_date(uint16_t yyyy, uint8_t mm, uint8_t dd, uint8_t wd) {
      year = yyyy;
      month = mm;
      day = dd;
      weekday = wd;
    }
    void set_time(uint8_t hh, uint8_t mm, uint8_t ss) {
      hour = hh;
      minute = mm;
      second = ss;
    }
};

#endif // DEF_GPSCOMMON
