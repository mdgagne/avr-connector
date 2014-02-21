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
#include "../avr-shared/pi_protocol.h"

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
avr_connector::~avr_connector ()
    {
    close (uart_stream);
    }

// ************************************************************
pit_byte_t avr_connector::read_byte (byte_address_t addr)
    {
    // Send the request
    const pi_request_t request =  
        {
        start_request, 
        (pif_read << 4) | (pit_byte),
        addr
        };

    int count = uart_send (request);

    // Check for successful send and read the response
    pi_response_t response = {0};    
    if (sizeof (request) == count)
        {
        // receieve the data (blocking)
        count = uart_recv (response);
        }

    // Expecting to receive a full response
    if (count != sizeof (response))
        {
        throw std::length_error ("Wrong number of bytes"); 
        }          

    // Return the pit_byte_t data
    return pit_byte_t (response.data[0]);
    }

// ************************************************************
// FIXME
pit_word_t avr_connector::read_word (word_address_t addr) {return 0;}

// ************************************************************
// FIXME
pit_dword_t avr_connector::read_dword (dword_address_t addr) {return 0;}

// ************************************************************
// FIXME
pit_float_t avr_connector::read_float (float_address_t addr) {return 0;}

// ************************************************************
int avr_connector::uart_send (const pi_request_t& request) 
    {
    int count = 0;
    if (-1 != uart_stream)
        {
        count = write (
            uart_stream, 
            reinterpret_cast<const char*> (&request), 
            sizeof (request));
        }

    return count;
    }

// ************************************************************
int avr_connector::uart_recv (pi_response_t& response) 
    {
    int count = 0;
    while (count < sizeof (response))
        {
        const int recv = read (
            uart_stream, 
            reinterpret_cast<char*> (&response), 
            sizeof (response));

        // Check for err
        if (-1 == recv)
            {
            break;
            }

        count += recv;
        }

    return count;
    }
}; // pimash

