#ifndef _TIMESTUFF_H
#define _TIMESTUFF_H

#include <stdint.h>
#include <time.h>

typedef struct tm tm_t;

/*
typedef struct {
  char* string;
  uint32_t last_run;
} time_struct;
*/

void clear_hms(tm_t * thetime) ;
void next_wday(tm_t * thetime, uint8_t wday);

#define next_week(x) next_wday(x,(*(x)).tm_wday)

#endif /* _TIMESTUFF_H */

