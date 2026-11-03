
#pragma once

#include <Arduino.h>
#include <avr/interrupt.h>

// Task 1 LEDs: PC1, PC2, PC3
#define LED0_reset()  (PORTC &= ~_BV(PC1))
#define LED1_reset()  (PORTC &= ~_BV(PC2))
#define LED2_reset()  (PORTC &= ~_BV(PC3))

#define LED0_set()    (PORTC |= _BV(PC1))
#define LED1_set()    (PORTC |= _BV(PC2))
#define LED2_set()    (PORTC |= _BV(PC3))

#define LED0_toggle() (PORTC ^= _BV(PC1))
#define LED1_toggle() (PORTC ^= _BV(PC2))
#define LED2_toggle() (PORTC ^= _BV(PC3))

// Task 2 LEDs: PD7, PD2
#define LED3_reset()  (PORTD &= ~_BV(PD7))
#define LED4_reset()  (PORTD &= ~_BV(PD2))

#define LED3_set()    (PORTD |= _BV(PD7))
#define LED4_set()    (PORTD |= _BV(PD2))

#define LED3_toggle() (PORTD ^= _BV(PD7))
#define LED4_toggle() (PORTD ^= _BV(PD2))

// Task 3 LED: PD5
#define LED5_reset()  (PORTD &= ~_BV(PD5))
#define LED5_set()    (PORTD |= _BV(PD5))
#define LED5_toggle() (PORTD ^= _BV(PD5))

// Task 5
#define TASK5_PWM_FREQUENCY 1000UL
#define TASK5_PWM_PRESCALER 1UL
#define TASK5_PWM_TOP ((CLK_IO / (TASK5_PWM_PRESCALER * TASK5_PWM_FREQUENCY)) - 1)

// Buttons
#define btn0 (PIND & _BV(PD4))
#define btn1 (PIND & _BV(PD3))

// Constants
#define DELAY_LONG  100000UL
#define DELAY_SHORT 50000UL

#define CLK_IO 400000UL

// Timer2: Task4 CTC
#define T2_COMPARE 97U

// Prototypes
void task1_setup();
void task2_setup();
void task3_setup();
void task4_setup();
void task5_setup();
void task6_setup();

void task1();
void task2();
void task6();
