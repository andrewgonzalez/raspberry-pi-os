#include "mini_uart.h"

unsigned int turn = 0;

void kernel_main(unsigned int procID)
{
	char id;

	// I can't get the type casting from int to char to work so...
	switch (procID) {
		case 0:
			id = '0';
			break;
		case 1:
			id = '1';
			break;
		case 2:
			id = '2';
			break;
		case 3:
			id = '3';
			break;
		default:
			id = 'f';
	}

	if (0 == procID) {  // only want proc 0 to init uart
		uart_init();
	}

	while (turn != procID) {}  // spin until it's your turn

	uart_send_string("Hello, world from processor ");
	uart_send(id);
	uart_send_string("!\r\n");
	turn++;

	while (0 == procID) {  // only proc 0 will send/receive from uart
		uart_send(uart_recv());
	}
}
