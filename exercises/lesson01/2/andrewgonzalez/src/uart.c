#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	while (get32(UART_FR_REG) & (1<<5))
	{
		; // spin while transmit FIFO is full
	}
	put32(UART_DR_REG, c);
}

char uart_recv ( void )
{
	while (get32(UART_FR_REG) & (1<<4))
	{
		; // spin while receive FIFO empty
	}
	return (get32(UART_DR_REG) & 0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt0 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt0 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	// Assuming 48Mhz UART clock frequency.
	// Going to try 115200 baud rate.
	// Formulas from PrimeCell UART (PL011) Technical Reference Manual (page 3-10)
	// baud rate divisor = 48MHz / (16 * 115200) = 26.041666666...
	// fractional part = (0.041666666 * 64) + 0.5 = 3.166666624
	// IBRD = 26
	// FBRD = 3
	put32(UART_CR_REG,0);       // Disable the UART
	put32(UART_IMSC_REG,0);     // Disable UART interrupts
	put32(UART_IBRD_REG,26);    // Set IBRD and FBRD
	put32(UART_FBRD_REG,3);
	put32(UART_LCRH_REG,112);   // Enable FIFOs, set word length to 8 bits

	put32(UART_CR_REG,769);     // Enable UART w/o flow control
}
