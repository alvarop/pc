#include "commands.h"

#include <stdio.h>
#include <string.h>

void command_sayhi(void);
void command_test(void);

command_t commands[] = {
  {command_sayhi, "sayhi"},
  {command_test, "test"},
  {NULL, NULL} };

void command_sayhi(void)
{
  printf("Hello!\n");
}

void command_test(void)
{
  printf("Testing!!!\n");
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

