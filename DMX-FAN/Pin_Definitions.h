//
//  Pin_Definitions.h
//  DMX-FAN
//
//  Created by Samuel Dewan on 2016-02-02.
//  Copyright © 2016 Samuel Dewan and Maxim Zakirov. All rights reserved.
//

#ifndef Pin_Definitions_h
#define Pin_Definitions_h

#include <avr/io.h>

// MARK: LEDs
#define RX_STATUS_PORT 	PORTD
#define RX_STATUS_DDR	DDRD
#define RX_STATUS_NUM  	PIND3
#define RX_STATUS_PWM   OCR2B

// MARK: Motor Driving
#define EN_1_2_PORT 	PORTD
#define EN_1_2_DDR      DDRD
#define EN_1_2_NUM  	PIND5

#define EN_3_4_PORT 	PORTD
#define EN_3_4_DDR      DDRD
#define EN_3_4_NUM  	PIND6

#define IN_1_PORT       PORTB
#define IN_1_DDR        DDRB
#define IN_1_NUM        PINB1 //OC1A
#define IN_1_PWM        OCR1A

#define IN_2_PORT       PORTD
#define IN_2_DDR        DDRD
#define IN_2_NUM        PIND7

#define IN_3_PORT       PORTB
#define IN_3_DDR        DDRB
#define IN_3_NUM        PINB2 //OC1B
#define IN_3_PWM        OCR1B

#define IN_4_PORT       PORTB
#define IN_4_DDR        DDRB
#define IN_4_NUM        PINB0 //CLKO


// MARK: DIP Switch

#define DIP_0_PORT       PORTC
#define DIP_0_DDR        DDRC
#define DIP_0_PIN        PINC
#define DIP_0_NUM        PINC5

#define DIP_1_PORT       PORTC
#define DIP_1_DDR        DDRC
#define DIP_1_PIN        PINC
#define DIP_1_NUM        PINC4

#define DIP_2_PORT       PORTC
#define DIP_2_DDR        DDRC
#define DIP_2_PIN        PINC
#define DIP_2_NUM        PINC3

#define DIP_3_PORT       PORTC
#define DIP_3_DDR        DDRC
#define DIP_3_PIN        PINC
#define DIP_3_NUM        PINC2

#define DIP_4_PORT       PORTC
#define DIP_4_DDR        DDRC
#define DIP_4_PIN        PINC
#define DIP_4_NUM        PINC1

#define DIP_5_PORT       PORTC
#define DIP_5_DDR        DDRC
#define DIP_5_PIN        PINC
#define DIP_5_NUM        PINC0

#define DIP_6_PORT       PORTB
#define DIP_6_DDR        DDRB
#define DIP_6_PIN        PINB
#define DIP_6_NUM        PINB5

#define DIP_7_PORT       PORTB
#define DIP_7_DDR        DDRB
#define DIP_7_PIN        PINB
#define DIP_7_NUM        PINB4

#define DIP_8_PORT       PORTB
#define DIP_8_DDR        DDRB
#define DIP_8_PIN        PINB
#define DIP_8_NUM        PINB3


#endif /* Pin_Definitions_h */
