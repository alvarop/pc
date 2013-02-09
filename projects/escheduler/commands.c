#include "commands.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void command_bedon(void);
void command_rackon(void);
void command_alloff(void);

command_t commands[] = {
  {command_bedon, "bedon"},
  {command_rackon, "rackon"},
  {command_alloff, "alloff"},
  {NULL, NULL} };

void command_bedon(void) {
  printf("Bed lights on\n");
  system("swrite 21 115200 30 ff ff ff");
  usleep(10000); // Repeat to make sure it turns on (no ack's yet)
  system("swrite 21 115200 30 ff ff ff");
}

void command_rackon(void) {
  printf("Bike rack lights on\n");
  system("swrite 21 115200 20 ff ff ff");
  usleep(10000); // Repeat to make sure it turns on (no ack's yet)
  system("swrite 21 115200 20 ff ff ff");
}

void command_alloff(void) {
  printf("All lights off\n");
  system("swrite 21 115200 00 00 00 00");
  usleep(10000); // Repeat to make sure it turns off (no ack's yet)
  system("swrite 21 115200 00 00 00 00");
}

void run_event(event_t * event) {
  command_t * cmd_ptr = commands;
   
  while((cmd_ptr->fn != NULL) && (cmd_ptr->alias != NULL)) {
    if(strncmp(cmd_ptr->alias, event->command, strlen(cmd_ptr->alias)) == 0) {
      cmd_ptr->fn();
      break;
    }
    cmd_ptr++;
  }
}

