#ifndef RASPBOOTIN2_PLATFORM
#define RASPBOOTIN2_PLATFORM

    // uncomment the line you want to build for
    //#define PLATFORM_RPI
    #define PLATFORM_RPIBP
    //#define PLATFORM_RPI2

    #ifdef PLATFORM_RPI
        #define PBASE 0x20000000
        #define PNAME "Raspberry Pi"
    #elif defined PLATFORM_RPIBP
        #define PBASE 0x20000000
        #define PNAME "Raspberry Pi Model B+"
    #elif defined PLATFORM_RPI2
        #define PBASE 0x3F000000
        #define PNAME "Raspberry Pi 2"
    #endif

#define SYSTIMERCLO    (PBASE+0x3004)
#define ARM_TIMER_LOD  (PBASE+0xB400)
#define ARM_TIMER_VAL  (PBASE+0xB404)
#define ARM_TIMER_CTL  (PBASE+0xB408)
#define ARM_TIMER_DIV  (PBASE+0xB41C)
#define ARM_TIMER_CNT  (PBASE+0xB420)

#define GPIOBASE        (PBASE+0x00200000)
#define GPFSEL0         (GPIOBASE+0x0000)
#define GPFSEL1         (GPIOBASE+0x0004)
#define GPFSEL2         (GPIOBASE+0x0008)
#define GPFSEL3         (GPIOBASE+0x000C)
#define GPFSEL4         (GPIOBASE+0x0010)
#define GPSET0          (GPIOBASE+0x001C)
#define GPCLR0          (GPIOBASE+0x0028)
#define GPSET1          (GPIOBASE+0x0020)
#define GPCLR1          (GPIOBASE+0x002C)
#define GPPUD           (GPIOBASE+0x0094)
#define GPPUDCLK0       (GPIOBASE+0x0098)

/**
 * \brief put a 32-bit word to a specific address
 * \param[in] r0 the address to write to
 * \param[in] r1 the value for writing
 * \author David Welch
 **/
extern void PUT32 ( unsigned int, unsigned int );
/**
 * \brief get a 32-bit word from an address
 * \param[in] r0 the address to read from
 * \return the read value
 * \author David Welch
 **/
extern unsigned int GET32 ( unsigned int );
/**
 * \brief jump; just waste time
 * \author David Welch
 **/
extern void dummy ( unsigned int );

/**
 * \brief jump to the specified address
 * \param[in] r0 the address to jump to
 * \author Stefan Naumann
 **/
extern void BOOTUP ( unsigned int );

#endif
