
// https://forum.arduino.cc/t/time-h-convert-to-time_t/61351/7

#include <Time.h>
#include <TimeLib.h>

// https://github.com/JChristensen/Timezone
#include <Timezone.h>


time_t convert_to_unix_time(int YYYY, byte MM, byte DD, byte hh, byte mm, byte ss)
{
  tmElements_t tmSet;
  tmSet.Year = YYYY - 1970;
  tmSet.Month = MM;
  tmSet.Day = DD;
  tmSet.Hour = hh;
  tmSet.Minute = mm;
  tmSet.Second = ss;
  return makeTime(tmSet);         //convert to time_t
}

GPSTime localTime;

GPSTime& getLocalTime(Timezone& tz, GPSTime& utc_time)
{
  TimeChangeRule *tcr; // pointer to the time change rule, use to get the TZ abbrev
  time_t utc_time_t = convert_to_unix_time(utc_time.year, utc_time.month, utc_time.day, utc_time.hour, utc_time.minute, utc_time.second);
  time_t local_time_t = tz.toLocal(utc_time_t, &tcr);
  
  localTime.set_date(year(local_time_t),month(local_time_t), day(local_time_t), weekday(local_time_t));
  localTime.set_time(hour(local_time_t), minute(local_time_t), second(local_time_t));

  return localTime;
}

// https://forum.arduino.cc/t/how-to-calculate-number-of-week-and-number-of-day/44587
uint16_t getWorkWeek(GPSTime& time) {
  uint16_t t_year = time.year;  // full year
  uint16_t t_month = time.month; // 1-12
  uint16_t t_days = time.day; // 1-31
  uint16_t t_weekday = time.weekday; // 1(Sun)-7(Sat)

  int days_month_start[]={0,31,59,90,120,151,181,212,243,273,304,334};    // Number of days at the beginning of the month in a not leap year.
  uint16_t days_in_year = 0;
  uint16_t week = 0;

  days_in_year = days_month_start[t_month - 1] + t_days;
  bool leap_year = ((t_year % 4 == 0 && t_year % 100 != 0) ||  t_year % 400 == 0);
  if ( t_month > 2 && leap_year) {
    days_in_year ++;
  }

  uint16_t number_of_weeks_in_year = days_in_year / 7;
  uint16_t remain_days = days_in_year % 7;

  if (remain_days) {
    number_of_weeks_in_year ++;
  }
  if (remain_days > t_weekday) {
    number_of_weeks_in_year ++;    
  }
  // if last week of calendar is not full, ww01 starts on the same week
  if (number_of_weeks_in_year == 53) {
    int full_days_in_year = leap_year ? 366 : 365;
    int days_remaining_in_year = full_days_in_year - days_in_year;
    if ( t_weekday + days_remaining_in_year < 7) {
      number_of_weeks_in_year = 1;
    }
  }
  return number_of_weeks_in_year;  
}

// testing work of the week
//void test_date(uint16_t y, uint16_t m, uint16_t d, uint16_t wd) {
//  GPSTime tt;
//  tt.set_time(10,11,12);
//
//  tt.set_date(y, m, d, wd);
//  sprintf(get_buf(),"DDD: %s ww%02d", tt.str(), getWorkWeek(tt));
//  Serial.println(get_buf());  
//}
//  test_date(2022, 1, 1, 7);
//  test_date(2022, 1, 2, 1);
//  test_date(2022, 04, 25, 2);
//  test_date(2022, 04, 24, 1);
//  test_date(2022, 04, 23, 7);
//  test_date(2022, 12, 26, 2);
//  test_date(2023, 1, 2, 2);
//  test_date(2023, 4, 10, 2);
//  test_date(2023, 12, 30, 7);
//  test_date(2021, 12, 27, 2);

// US Pacific Time Zone (Portland)
TimeChangeRule usPDT = {"PDT", Second, Sun, Mar, 2, -420};
TimeChangeRule usPST = {"PST", First, Sun, Nov, 2, -480};
Timezone timezonPDX(usPDT, usPST);

// Malaysia
TimeChangeRule my_dt = {"MY", Second, Sun, Mar, 2, 480};
Timezone timezonMY(my_dt);

// India
TimeChangeRule ind_dt = {"IND", Second, Sun, Mar, 2, 330};
Timezone timezonIND(ind_dt);

// IDC
TimeChangeRule idc_dt = {"PDT", Last, Sun, Mar, 2, 180}; // this is actually not correct, need to be '-46' (two days before Sunday - Friday), but the library does not support it, that is okay
TimeChangeRule idc_st = {"PST", First, Sun, Oct, 2, 120};
Timezone timezonIDC(idc_dt, idc_st);

// Russia Moscow
TimeChangeRule ind_ru = {"MOW", Second, Sun, Mar, 2, 180};
Timezone timezonMOW(ind_ru);
