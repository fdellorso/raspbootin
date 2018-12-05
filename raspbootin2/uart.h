/**
 * \file uart.h
 * \author Stefan Naumann
 * \date 08 April 2017
 * \brief prototypes and definitions for UART-related code on the Raspberry Pi,
 * most of the actual code is directly taken from dwelch67s "uart05"-demo.
 * See the legal notice on the bottom of the header-file
 **/

#ifndef RASPBOOTIN2_UART
#define RASPBOOTIN2_UART

#include "platform.h"

#define AUX_ENABLES     (PBASE+0x00215004)
#define AUX_MU_IO_REG   (PBASE+0x00215040)
#define AUX_MU_IER_REG  (PBASE+0x00215044)
#define AUX_MU_IIR_REG  (PBASE+0x00215048)
#define AUX_MU_LCR_REG  (PBASE+0x0021504C)
#define AUX_MU_MCR_REG  (PBASE+0x00215050)
#define AUX_MU_LSR_REG  (PBASE+0x00215054)
#define AUX_MU_MSR_REG  (PBASE+0x00215058)
#define AUX_MU_SCRATCH  (PBASE+0x0021505C)
#define AUX_MU_CNTL_REG (PBASE+0x00215060)
#define AUX_MU_STAT_REG (PBASE+0x00215064)
#define AUX_MU_BAUD_REG (PBASE+0x00215068)

/**
 * \brief return the content of the control register
 * \author David Welch
 **/
unsigned int uart_lcr ( void );
/**
 * \brief return the currently received value from the UART-controller
 * \note does not create an input-queue!
 * \author David Welch
 **/
unsigned int uart_recv ( void );
/**
 * \brief check for a new character (return 1 if available, 0 if not)
 * \author David Welch
 **/
unsigned int uart_check ( void );
/**
 * \brief send a character through the UART
 * \param[in] c the character to send
 * \author David Welch
 **/
void uart_send ( unsigned int c );
/**
 * \brief will send a string through the UART
 * \param[in] str the string to be sent
 * \author Stefan Naumann
 **/
void uart_puts ( char* str );

/**
 * \brief wait until every operation ended (?)
 * \author David Welch
 **/
void uart_flush ( void );
/**
 * \brief initiate the UART-interface 
 * \author David Welch
 **/
void uart_init ( void );

#endif


// Copyright of the UART-code (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
