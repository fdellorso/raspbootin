#include "platform.h"
#include "uart.h"

#include <stdint.h>

/// the upper end of the memory
#define LOADER_ADDR 0x2000000

int main ()
{
    unsigned int ra;

    // Set Output GPIO47  ACT LED
    ra  = GET32(GPFSEL4);
    ra &= ~(7 << 21);
    ra |= 1 << 21;
    PUT32(GPFSEL4, ra);

    // JTAG GPIO Settings
    PUT32(GPPUD, 0);
    for (ra = 0; ra < 150; ra++)
        dummy(ra);
    // PUT32(GPPUDCLK0,(1<<4)|(1<<22)|(1<<23)|(1<<24)|(1<<25)|(1<<27));
    PUT32(GPPUDCLK0, (1 << 5) | (1 << 6) | (1 << 12) | (1 << 13) | (1 << 22) | (1 << 26));
    for (ra = 0; ra < 150; ra++)
        dummy(ra);
    PUT32(GPPUDCLK0, 0);

    ra  = GET32(GPFSEL0);
    // ra&=~(7<<12); //gpio4
    // ra|=2<<12; //gpio4 alt5 ARM_TDI
    ra &= ~(7 << 15); //gpio5
    ra |= 2 << 15;    //gpio5 alt5 ARM_TDO
    ra &= ~(7 << 18); //gpio6
    ra |= 2 << 18;    //gpio6 alt5 ARM_RTCK
    PUT32(GPFSEL0, ra);

    ra  = GET32(GPFSEL1);
    ra &= ~(7 << 6); //gpio12
    ra |= 2 << 6;    //gpio12  alt5  ARM_TMS
    ra &= ~(7 << 9); //gpio13
    ra |= 2 << 9;    //gpio13 alt5 ARM_TCK
    PUT32(GPFSEL1, ra);

    ra  = GET32(GPFSEL2);
    ra &= ~(7 << 6); //gpio22
    ra |= 3 << 6;    //gpio22 alt4 ARM_TRST
    // ra&=~(7<<9); //gpio23
    // ra|=3<<9; //gpio23 alt4 ARM_RTCK
    // ra&=~(7<<12); //gpio24
    // ra|=3<<12; //gpio24 alt4 ARM_TDO
    // ra&=~(7<<15); //gpio25
    // ra|=3<<15; //gpio25 alt4 ARM_TCK
    ra &= ~(7 << 18); //gpio26
    ra |= 3 << 18;    //gpio26 alt4 ARM_TCI
    // ra&=~(7<<21); //gpio27
    // ra|=3<<21; //gpio27 alt4 ARM_TMS
    PUT32(GPFSEL2, ra);

    // init the uart-hardware
    uart_init();
    
    // print the header and some build-info    
    uart_puts("Raspbootin V2\r\n");
    uart_puts("Built for: ");
    uart_puts(PNAME);
    uart_puts("\r\n");

again:
    // send the start-code for the raspbootcom-application
    uart_puts("\x03\x03\x03");
    
    // the size of the kernel has been received
    uint32_t size = 0;
    size |= uart_recv();
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
    while(size > 0) 
    {
	    *kernel = uart_recv();
	    kernel++;
	    size--;
    }

    // Kernel is loaded at 0x8000, call it via function pointer
    uart_puts("boot...\r\n");
    BOOTUP(0x8000);
}

