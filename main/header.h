#include "Arduino.h"

//Macros
// LED RESET (clear bits)
  //LED task1
#define LED0_reset()  (PORTD &= ~(1 << 0))
#define LED1_reset()  (PORTD &= ~(1 << 1))
#define LED2_reset()  (PORTD &= ~(1 << 2))
//#define LED3_reset()  (PORTD &= ~(1 << 3))
  //LED task2
#define LED3_reset()  (PORTC &= ~(1 << 3))
#define LED4_reset()  (PORTD &= ~(1 << 4))
  //LED task3
#define LED5_reset()  (PORTD &= ~(1 << 5))

#define LED6_reset()  (PORTD &= ~(1 << 6))
#define LED7_reset()  (PORTD &= ~(1 << 7))

// LED SET (set bits)
  //LED task1
#define LED0_set()  (PORTD |= (1 << 0))
#define LED1_set()  (PORTD |= (1 << 1))
#define LED2_set()  (PORTD |= (1 << 2))
//#define LED3_set()  (PORTD |= (1 << 3))
  //LED task2
#define LED3_set()  (PORTC |= (1 << 3))
  //LED task3
#define LED4_set()  (PORTD |= (1 << 4))
#define LED5_set()  (PORTD |= (1 << 5))
#define LED6_set()  (PORTD |= (1 << 6))
#define LED7_set()  (PORTD |= (1 << 7))

// LED TOGGLE
  //LED task1
#define LED0_toggle()  (PORTD ^= (1 << 0))
#define LED1_toggle()  (PORTD ^= (1 << 1))
#define LED2_toggle()  (PORTD ^= (1 << 2))
//#define LED3_toggle()  (PORTD ^= (1 << 3))
  //LED task2
#define LED3_toggle()  (PORTC ^= (1 << 3))
  //LED task3
#define LED4_toggle()  (PORTD ^= (1 << 4))
#define LED5_toggle()  (PORTD ^= (1 << 5))
#define LED6_toggle()  (PORTD ^= (1 << 6))
#define LED7_toggle()  (PORTD ^= (1 << 7))

#define btn0 (PINC & 1)       //PC0
#define btn1 (PIND & (1<<3))  //PD3, INT1

//Prototipuri
void task1_setup();
void task2_setup();
void task3_setup();

void task1();
void task2();
