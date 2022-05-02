
#define TIMER_RESOLUTION_MS 100000

class GPSTimerMS {
  private:
    uint32_t last_tick_ms = 0;
    uint32_t timeout_ms = 0;
  public:
    GPSTimerMS(uint32_t _timeout_ms) {
      timeout_ms = _timeout_ms;
    }

    bool reset() {
      last_tick_ms = millis() % TIMER_RESOLUTION_MS;
      //    sprintf(get_buf(), "reset: %lu", last_tick_ms);
      //    Serial.println(get_buf());
    }

    bool fired() {
      uint32_t current_ms_time = millis();

      uint32_t current_ms_mod = current_ms_time % TIMER_RESOLUTION_MS;
      uint32_t current_ms = current_ms_mod;

      if (current_ms < last_tick_ms) {
        current_ms += TIMER_RESOLUTION_MS;
      }
      uint32_t time_delta = current_ms - last_tick_ms;
      bool expired = (time_delta >= timeout_ms);
      //    sprintf(get_buf(), "reset: current_ms_time=%lu last_tick_ms=%lu current_ms=%lu time_delta=%lu", current_ms_time, last_tick_ms, current_ms, time_delta);
      //    Serial.println(get_buf());
      return expired;
    }
};
