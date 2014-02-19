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
float avr_connector::get_temp_sp (void)
    {
    return (150.0);
    }
}; // pimash

