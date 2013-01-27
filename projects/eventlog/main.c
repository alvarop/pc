/** @file main.c
*
* @brief Event logger
*
* @author Alvaro Prieto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "serial.h"
#include "main.h"

pthread_t serial_thread;

#define PRINT_TIME time(&raw_time); \
  p_tm = gmtime ( &raw_time ); \
  printf("%02d/%02d/%4d - %02d:%02d:%02d", p_tm->tm_mon+1, p_tm->tm_mday, p_tm->tm_year+1900, p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);
  
FILE* f_log;
time_t raw_time;
struct tm* p_tm;

int main( int argc, char *argv[] )
{
  int32_t rc;

  // Handle interrupt events to make sure files are closed before exiting
  (void) signal( SIGINT, sigint_handler );

  // Make sure input is correct
  if( argc < 2 )
  {
    printf("Usage: %s port baudrate\n", argv[0]);
    return 0;
  }

  PRINT_TIME;
  printf(" Threaded Event Logger\r\n");
  // Convert string serial number to integer and open port
  if( serial_open( atoi( argv[1] ), atoi( argv[2] ), &process_packet ) )
  {
    printf("Error opening serial port.\r\n");
    exit(-1);
  }

  f_log = fopen("log.csv", "a");
  fprintf(f_log, "%ld,Start Logging,,\n", time(NULL));
  fclose(f_log);

  rc = pthread_create( &serial_thread, NULL, serial_read_thread, NULL );

  if (rc)
  {
    printf("Error creating serial thread\n");
    exit(-1);
  }


  for(;;)
  {
    sleep(1);
  }


  return 0;
}

/*******************************************************************************
 * @fn     void process_packet( uint8_t* buffer, uint32_t size )
 * @brief  Process incoming serial packet
 * ****************************************************************************/
uint8_t process_packet( uint8_t* buffer, uint32_t size )
{
  
  packet_header_t* packet_header = (packet_header_t*) buffer;
 
  if(packet_header->type == IO_CHANGE) {
      f_log = fopen("log.csv", "a");
      fprintf(f_log, "%ld,%d,%d,%d\n", time(NULL), packet_header->source, packet_header->type, packet_header->flags);
      fclose(f_log);
      PRINT_TIME;
      printf(" IO Change Message from %d - 0x%02X\n", packet_header->source, packet_header->flags );
  } else {
    for( uint16_t buffer_index = 0; buffer_index < size; buffer_index++ )
    {
      printf( "%02X ", buffer[buffer_index] );
    }
    printf("\n");
  }

  return 1;
}


/*******************************************************************************
 * @fn     void sigint_handler( int32_t sig )
 * @brief  Handle interrupt event (SIGINT) so program exits cleanly
 * ****************************************************************************/
void sigint_handler( int32_t sig )
{

    pthread_cancel( serial_thread );
  
    f_log = fopen("log.csv", "a");
    fprintf(f_log, "%ld,Done Logging\n", time(NULL));
    fclose(f_log);
  
    // Close the serial port
    serial_close();
    PRINT_TIME;
    printf("\nExiting...\n");
    exit(sig);
}

