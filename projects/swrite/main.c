/** @file main.c
*
* @brief Command-line Serial Writer
*
* @author Alvaro Prieto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include "serial.h"

#define MAX_MESSAGE_SIZE (64)

int main( int argc, char *argv[] )
{
  
  uint32_t message_size;
  uint8_t message[MAX_MESSAGE_SIZE];
  
  // Make sure input is correct
  if( argc < 3 )
  {
    printf("Usage: %s port baudrate message(02 25 d3 f5..)\n", argv[0]);
    return 0;
  }
    
  message_size = argc - 3;
  
  if( message_size > MAX_MESSAGE_SIZE ) {
    message_size = MAX_MESSAGE_SIZE;
    printf("Too many bytes! Only the first %u will be sent\n", MAX_MESSAGE_SIZE);
  }
  
  for(uint8_t byte_index = 0; byte_index < message_size; byte_index++) {
    message[byte_index] = (uint8_t)strtoul(argv[byte_index+3], NULL, 16);
    
    printf("%02x ", message[byte_index] );
  }
  
  printf("\n");
  
  // Convert string serial number to integer and open port
  if( serial_open( strtoul( argv[1], NULL, 10 ), strtoul( argv[2], NULL, 10 ), NULL ) )
  {
    printf("Error opening serial port.\r\n");
    exit(-1);
  }
  
  send_serial_message( message, message_size );

  // Close the serial port
  serial_close();

  return 0;
}






