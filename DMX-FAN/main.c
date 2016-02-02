//
//  main.c
//  DMX-FAN
//
//  Created by Samuel Dewan on 2016-02-02.
//  Copyright © 2016 Samuel Dewan and Maxim Zakirov. All rights reserved.
//


#include <stdio.h>
#include <avr/interrupt.h>

#include "Pin_Definitions.h"

// MARK: Global Variables
volatile uint32_t millis, lastRX;       //Clock values

// MARK: Function Declarations
static void main_loop (void);

// MARK: Function Definitions

void initIO(void) {
	// LEDs
    RX_STATUS_DDR |= (1<<RX_STATUS_NUM);
    // Motor
    EN_1_2_DDR |= (1<<EN_1_2_NUM);
    EN_3_4_DDR |= (1<<EN_3_4_NUM);
    IN_1_DDR |= (1<<IN_1_NUM);
    IN_2_DDR |= (1<<IN_2_NUM);
    IN_3_DDR |= (1<<IN_3_NUM);
    IN_4_DDR |= (1<<IN_4_NUM);
    // DIP
    DIP_0_DDR &= ~(1<<DIP_0_NUM);
    DIP_0_PORT |= (1<<DIP_0_NUM);
    DIP_1_DDR &= ~(1<<DIP_1_NUM);
    DIP_1_PORT |= (1<<DIP_1_NUM);
    DIP_2_DDR &= ~(1<<DIP_2_NUM);
    DIP_2_PORT |= (1<<DIP_2_NUM);
    DIP_3_DDR &= ~(1<<DIP_3_NUM);
    DIP_3_PORT |= (1<<DIP_3_NUM);
    DIP_4_DDR &= ~(1<<DIP_4_NUM);
    DIP_4_PORT |= (1<<DIP_4_NUM);
    DIP_5_DDR &= ~(1<<DIP_5_NUM);
    DIP_5_PORT |= (1<<DIP_5_NUM);
    DIP_6_DDR &= ~(1<<DIP_6_NUM);
    DIP_6_PORT |= (1<<DIP_6_NUM);
    DIP_7_DDR &= ~(1<<DIP_7_NUM);
    DIP_7_PORT |= (1<<DIP_7_NUM);
    DIP_8_DDR &= ~(1<<DIP_8_NUM);
    DIP_8_PORT |= (1<<DIP_8_NUM);
}

int main(void) {
    cli();                                  // Clear interupts
    
	initIO();                               // Set pin modes
    
    // Timer 0 (Clock)
    TCCR0A |= (1 << WGM01);                 // Set the Timer Mode to CTC
    OCR0A = 125;                            // Set the value to count to 125 (1 millisecond at 8Mhz where prescaler = 64)
    TIMSK0 |= (1 << OCIE0A);                // Set the ISR COMPA vector
    TCCR0B |= (1 << CS01) | (1 << CS00);    // set prescaler to 64 (and therefor start timer 0)
    
    // Timer 1 (PWM 1)
    TCCR1A |= 0xF0;							//Inverted mode
    TCCR1A |= (1 << WGM10);					//Mode 5, Fast PWM, 8 bit
    TCCR1B |= (1 << CS10) | (1 << WGM12);	//set prescaler to 0 and start timer 1
    
    // Timer 2 (PWM 2)
    TCCR2A |= 0xF0;							//Inverted mode
    TCCR2A |= (1 << WGM20)| (1 << WGM21);	//Mode 3, fast PWM
    TCCR2B |= (1 << CS20);					//set prescaler to 0 and start timer 2

    //Initialize Values to 0
    IN_1_PWM = 0;
    IN_3_PWM = 0;
    RX_STATUS_PWM = 0;
    
    //Initialize USART
    UBRR0H = 0;								//250kbps baud rate for a 8MHz system clock
    UBRR0L = 1;
    UCSR0A = 0;								//Only receiver enabled, RX interrupt enabled
    UCSR0B = 0x90;
    UCSR0C = 0x8e;							//8 data bits, 2 stop bits
    
    sei();                  // Enable interupts
    
    for (;;) {              // Run main loop for evermore
        main_loop();
	}
	return 0;               // never reached
}

void main_loop (void) {
    
}


// MARK: Interupt Service Routines
ISR (TIMER0_COMPA_vect) { 					//timer0 overflow interrupt (called every millisecond)
    millis++; 								//Increment clock every millisecond
}

/*
 DMX Channels
 
 Chan 1: Fan one speed
 Chan 2: Fan two speed
 Chan 3: Direction control
 
 F = Forward	R = Reverse
 
 M1		M2			Value
 F		F			0     - 64		(0% - 0.2509803922%)				Use 20%
 F		R			65   - 128		(0.2549019608% - 0.5019607843%)		Use 40%
 R		F			129 - 192		(0.5058823529% - 0.7529411765%)		Use 60%
 R		R			193 - 255		(0.7568627451% - 1%)				Use 80%
*/
