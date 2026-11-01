#include "header.h"

//Inițializări
void task1_setup() {
    DDRD |= 0b00000111;  // PD0-PD2: LED outputs
}

void task2_setup() {
    DDRD |= (1 << PD4);       // PD4: LED output
    DDRC |= (1 << PC3);       // PC3: LED output
    DDRC &= ~(1 << PC0);      // PC0: button input
    PORTC |= (1 << PC0);      // PC0: internal pull-up
}

// PD3 for external interrupt
void task3_setup() {
    DDRD |= (1 << PD5);       // PD5: output
    DDRD &= ~(1 << PD3);      // PD3: button input
    PORTD |= (1 << PD3);      // PD3: internal pull-up

    // INT1: falling edge
    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);

    EIMSK |= (1 << INT1);     // Enable INT1
    sei();                    // Enable global interrupts
}
const uint32_t delay_long = 100000;
const uint32_t delay_short = 50000;
volatile uint32_t timer = 0;
//Tasks
void task1(){
  //LED 0,1,2
  LED0_set();
  timer = delay_short;
  while(timer--);
  LED0_reset(); //LED0 off
  LED1_set(); //LED1 on

  timer = delay_short;
  while(timer--);
  LED1_reset(); //LED1 off
  LED2_set(); //LED2 on
  
  timer = delay_short;
  while(timer--);
  LED3_reset(); //LED3 off
  
  timer = delay_long;
  while(timer--);
}

bool task2_flag = 0;
bool buton_prev = 0;
void task2(){
  //LED 3 si 4
  //buton pe PC 0
  if((!buton_prev) && !btn0){
    task2_flag = !task2_flag;
    buton_prev = 1;  
  }
  if(buton_prev && btn0){
    buton_prev = 0;
  }
  if(task2_flag){
    LED3_set();   //LED3 on
    LED4_reset(); //LED4 off
  }
  else{
    LED3_reset(); //LED3 off
    LED4_set();   //LED4 on
  }
}
ISR(INT1_vect){
  LED4_toggle();
}

