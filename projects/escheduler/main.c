/** @file main.c
*
* @brief Event Scheduler
*
* @author Alvaro Prieto
*/
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "timestuff.h"
#include "commands.h"

event_t events[] = {
  {"bedon",   5,  44, (DAY_MON | DAY_WED)},
  {"rackon",  5,  45, (DAY_MON | DAY_WED)},
  {"alloff",  6,  30, DAY_ALL},
  {"bedon",   7,  24, (DAY_TUE | DAY_THU | DAY_FRI | DAY_SAT | DAY_SUN)},
  {"rackon",  7,  25, (DAY_TUE | DAY_THU | DAY_FRI | DAY_SAT | DAY_SUN)},
  {"alloff",  8,  00, DAY_ALL},
  {NULL, 0, 0, 0}};

#define ALARM_INTERVAL (1)
#define ALARM_FLAG (1)
uint32_t flags = 0;

void sigint_handler(int signal) {
  exit(0);
}

void sigalrm_handler(int signal) {
  flags |= ALARM_FLAG;
}

int main( int argc, char *argv[] )
{
  sigset_t mask, oldmask;

  // Configuration for sigsuspend to wait for SIGALRM
  sigemptyset (&mask);
  sigaddset (&mask, SIGALRM);
  sigprocmask (SIG_BLOCK, &mask, &oldmask);

  (void) signal(SIGINT, sigint_handler);
  (void) signal(SIGALRM, sigalrm_handler);
  
  tm_t * thetime;
  time_t raw_time, event_time;
  
  time(&raw_time);
  thetime = localtime(&raw_time);
  
  printf("escheduler started at %ld -- %02u/%02u/%04u %02u:%02u:%02u\n", time(NULL), thetime->tm_mday, thetime->tm_mon+1, thetime->tm_year+1900, thetime->tm_hour, thetime->tm_min, thetime->tm_sec);


  alarm(ALARM_INTERVAL);
  
  while(1) {
    sigsuspend (&oldmask); // Wait for a SIGALRM
    
    if(flags & ALARM_FLAG) {
      
  
      event_t* event_ptr = events;
      while(event_ptr->command != NULL) {
        
        time(&raw_time);
        thetime = localtime(&raw_time);
                
        // Does event happen today?
        if(event_ptr->day & (1 << thetime->tm_wday)) {
          clear_hms(thetime);
          thetime->tm_min = event_ptr->min;
          thetime->tm_hour = event_ptr->hour;
          event_time = mktime(thetime);

          if(event_time == raw_time) {
            run_event(event_ptr);
          }
        }
        
        event_ptr++;
      }      
      
      alarm(ALARM_INTERVAL);
    }
    
    flags &= ~ALARM_FLAG;
    
  }
  sigprocmask (SIG_UNBLOCK, &mask, NULL);
  
  return 0;
}


