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
  
  printf("escheduler started\n");
   
  alarm(ALARM_INTERVAL);
  
  while(1) {
    sigsuspend (&oldmask); // Wait for a SIGALRM
    
    if(flags & ALARM_FLAG) {
      printf("Alarm received!\n");
      alarm(ALARM_INTERVAL);
    }
    
    flags &= ~ALARM_FLAG;
    
  }
  sigprocmask (SIG_UNBLOCK, &mask, NULL);
  
  return 0;
}






