/*
 ************************************************************
 * PiMash - 
 * 	Interface to read/write data to avr-pimash controller
 ************************************************************
 */
#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <stdexcept>
#include <iostream>
#include <string>
#include "avr_connector.h"


namespace
{

}
namespace pimash
{
// ************************************************************
avr_connector::avr_connector (char* uart)
    : uart_stream (open (uart, O_RDWR | O_NOCTTY | O_NDELAY))
    {
    // Open ttyAMA0
    if (uart_stream == -1)
        {
        std::string err = std::string (uart) + std::string (" is not available");
        throw std::invalid_argument (err);
        }

    // Set the UART baud, data bits, and stop bits
    struct termios options;
	tcgetattr (uart_stream, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart_stream, TCIFLUSH);
	tcsetattr(uart_stream, TCSANOW, &options);
    }

// ************************************************************
// FIXME
pit_byte_t avr_connector::read_byte (void) {return 0;}

// ************************************************************
// FIXME

// ************************************************************
// FIXME
pit_word_t avr_connector::read_word (void) {return 0;}

// ************************************************************
// FIXME
pit_dword_t avr_connector::read_dword (void) {return 0;}

// ************************************************************
// FIXME
pit_float_t avr_connector::read_float (void) {return 0;}

// ************************************************************
// FIXME
int avr_connector::uart_send (unsigned char* buff, int size) {return 0;}

// ************************************************************
// FIXME
int avr_connector::uart_recv (unsigned char* buff, int size) {return 0;}
}; // pimash

