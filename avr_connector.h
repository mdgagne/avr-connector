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

        // TODO: Define read/write operations
        pit_byte_t read_byte (void);
        pit_word_t read_word (void);
        pit_dword_t read_dword (void);
        pit_float_t read_float (void);

    private:
        int uart_send (unsigned char* buff, int size);
        int uart_recv (unsigned char* buff, int size);

    private:    
        int uart_stream;
        std::vector<unsigned char> vecBuffer;
    };

}; // pimash

#endif // __LIB_PIMASH__


