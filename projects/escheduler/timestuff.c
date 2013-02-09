#include "timestuff.h"

void clear_hms(tm_t * thetime) {
  thetime->tm_hour = 0;
  thetime->tm_min = 0;
  thetime->tm_sec = 0;
  mktime(thetime);
}

void next_wday(tm_t * thetime, uint8_t wday) {
  time_t unixtime = mktime(thetime);
  int8_t day_offset = 7;
  
  if(wday > thetime->tm_wday) {
    day_offset = wday - thetime->tm_wday;
  } else {
    day_offset = wday + 7 - thetime->tm_wday;
  }

  unixtime += 60 * 60 * 24 * day_offset; 
  localtime_r(&unixtime, thetime);

}

