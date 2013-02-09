#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <stdint.h>

// Flags for the 'day' field in event_t
#define DAY_SUN (1 << 0)
#define DAY_MON (1 << 1)
#define DAY_TUE (1 << 2)
#define DAY_WED (1 << 3)
#define DAY_THU (1 << 4)
#define DAY_FRI (1 << 5)
#define DAY_SAT (1 << 6)
#define DAY_ALL (0x7F)

typedef struct {
  char* command;
  uint8_t hour;
  uint8_t min;
  uint8_t day;
} event_t;

typedef struct {
  void (* const fn)(void);
  char* alias;
} command_t;

void run_event(event_t * event);

#endif /* _COMMANDS_H */

