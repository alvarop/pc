/** @file main.h
*
* @brief Main definitions and data types
*
* @author Alvaro Prieto
*/
#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>

#define BUFFER_SIZE ( 512 )

/**
 * Packet header structure. The packet length byte is omitted, since the receive
 * function strips it away. Also, the cc2500_tx_packet function inserts it
 * automatically.
 */
typedef struct
{
  uint8_t destination;  // Packet destination
  uint8_t source;       // Packet source
  uint8_t type;         // Packet Type
  uint8_t flags;        // Misc flags
} packet_header_t;

//
// Packet Type Definitions (todo)
//
#define IO_CHANGE (0x01)


// Function Prototypes
uint8_t process_packet( uint8_t*, uint32_t );

void sigint_handler( int32_t sig );

#endif

