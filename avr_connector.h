/*
 ************************************************************
 * PiMash - 
 * 	Interface to read/write data to avr-pimash controller
 ************************************************************
 */
#ifndef __LIB_PIMASH__
#define __LIB_PIMASH__
#include <vector>
#include "../avr-shared/pi_protocol.h"

namespace pimash
{
// ************************************************************
// Reads/writes data from the pimash avr
class avr_connector
    {
    public:
        // Opens ttyAMA0, configures port for 115200/8/N/1
        avr_connector (char* uart);
        ~avr_connector ();

        // Read/Write operations
        pit_byte_t read_byte (byte_address_t addr);
        pit_word_t read_word (word_address_t addr);
        pit_dword_t read_dword (dword_address_t addr);
        pit_float_t read_float (float_address_t addr);

    private:
        // Send/Recv helpers
        int uart_send (const pi_request_t& request);
        int uart_recv (pi_response_t& response);

    private:    
        int uart_stream;
    };

}; // pimash

#endif // __LIB_PIMASH__


