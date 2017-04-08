#include "platform.h"
#include "uart.h"

#include <stdint.h>

/// the upper end of the memory
#define LOADER_ADDR 0x2000000

int main ()
{
    // init the uart-hardware
    usart_init();
    
    // print the header and some build-info    
    uart_puts("\r\nRaspbootin V2\r\n");
    uart_puts("#############\r\n");
    uart_puts("Built for: ");
    uart_puts(PNAME);
    uart_puts("\r\n#############\r\n");

again:
    // send the start-code for the raspbootcom-application
    uart_puts("\x03\x03\x03");
    
    // the size of the kernel has been received
    unsigned int size = uart_recv();
    size |= uart_recv() << 8;
    size |= uart_recv() << 16;
    size |= uart_recv() << 24;

    // the kernel is too big
    if (0x8000 + size > LOADER_ADDR) 
    {
        uart_puts("SE");
        goto again;
    } 
    else 
    {
        uart_puts("OK");
    }
    
    // get kernel
    uint8_t *kernel = (uint8_t*)0x8000;
    while(size-- > 0) 
    {
	    *kernel = uart_recv();
	    kernel++;
    }

    // Kernel is loaded at 0x8000, call it via function pointer
    uart_puts("booting kernel...");
    void (*fn) () = (void*)0x8000;
    fn();

    // fn() should never return. But it might, so make sure we catch it.
    // Wait a bit
    for(volatile int i = 0; i < 10000000; ++i) { }

    // Say goodbye and return to boot.S to halt.
    uart_puts("\r\n ## Goodbye lad! ##\r\n");
}

