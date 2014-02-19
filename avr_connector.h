/*
 ************************************************************
 * PiMash - 
 * 	Interface to read/write data to avr-pimash controller
 ************************************************************
 */
#ifndef __LIB_PIMASH__
#define __LIB_PIMASH_

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
        float get_temp_sp (void);
        
    private:    
        int uart_stream;
    };

}; // pimash

#endif // __LIB_PIMASH__


