//
// Forktest!
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct {
  float r;
  float g;
  float b;
} rgb_t;

//
// Fade rgb_led's from one color to another.
//
void fade(uint8_t address, rgb_t * from, rgb_t * to, uint32_t steps, uint32_t delay_ms) {
  rgb_t color = *from;
  rgb_t delta = { (to->r - from->r) / steps,
                  (to->g - from->g) / steps,
                  (to->b - from->b) / steps};
                  
  struct timespec delay = {0, delay_ms * 1000000};
  
  char command[64];
  
  while(steps-- > 0) {
    color.r += delta.r;
    color.g += delta.g;
    color.b += delta.b;
    
    snprintf(command, sizeof(command), "swrite 21 115200 %02X %02X %02X %02X", 
                                address,
                                (uint8_t)(color.r * 255),
                                (uint8_t)(color.g * 255),
                                (uint8_t)(color.b * 255));
    system(command);
    nanosleep(&delay, NULL);
  }
}

int main( int argc, char *argv[] )
{
  
  pid_t pid;
  
  // Child executes fade function
  if((pid=fork()) == 0) {
    rgb_t from = {0.0, 0.0, 0.0};
    rgb_t to = {1.0, 1.0, 1.0};
    fade(0x20, &from, &to, 60, 33);
  }
  

  
  return 0;
}


