/*
 *      timer2pwm.h
 *      
 *      Copyright 2009 Nathaniel Robert Lewis <linux.robotdude@gmail.com>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 * 
 *      This header controls pwm functions on timer 2
 * 
 */

#ifndef _TIMER_2_PWM
#define _TIMER_2_PWM 1

#include <avr/io.h>
#include <stdint.h>

//timer 2 prescalers
#define T2_PRESCALER_1 (1 << CS20)   // t2clock/1
#define T2_PRESCALER_8 (1 << CS21)   // t2clock/8
#define T2_PRESCALER_32 (1 << CS21) | (1 << CS20) // t2clock/32
#define T2_PRESCALER_64 (1 << CS22)  // t2clock/64
#define T2_PRESCALER_128 (1 << CS22) | (1 << CS20)// t2clock/128
#define T2_PRESCALER_256 (1 << CS22) | (1 << CS21)// t2clock/256
#define T2_PRESCALER_1024 (1 << CS22) | (1 << CS21) | (1 << CS20) // t2clock/1024

void init_timer2_pwm ( uint8_t prescaler, uint8_t invert ) {
	DDRD |= (1 << PORTD6) | (1 << PORTD7); //set the proper pins as outputs
	TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20); //set up the timer for standard mode
	if (invert) {                          //if inversion requested
		TCCR2A |= (1 << COM2A0) | (1 << COM2B0);//set the extra bits required for inverted output
	}
	TCCR2B = (prescaler & 0x07); //set the other mode bits and the prescaler (masks unused bits)
}

void set_pwm_2a ( uint8_t value ) {
	OCR2A = value;
}

void set_pwm_2b ( uint8_t value ) {
	OCR2B = value;
}

#endif
