//TODO : Macro uri pentru leduri 1-8 pe PORTD
//TODO : Macro uri pentru butoane pe PORTB
//TODO : Fisiere separate: functii, header, main

void task1_setup(){
  DDRD = DDRD | 0b00000111; //PD: 0-2 driver LED
}
void task2_setup(){
  DDRD = DDRD | 0b00011000; //PD: 3-4 driver pe LED
  DDRB = DDRB & 0b11111110; //PB: 0 intrare buton
  PORTB = PORTB | 0b00000001; //PB: 0 Pull-up
  //PORTD 
}
void setup() {
  // put your setup code here, to run once:
  // Punctul 1
    // PC:1-3 driver LED (pe anod)
  task1_setup();
  task2_setup();
  
}

const uint32_t delay_long = 100000;
const uint32_t delay_short = 50000;
volatile uint32_t timer = 0;
void task1(){
  PORTD |= 1; //LED1 on
  
  timer = delay_short;
  while(timer--);
  PORTD &= ~1; //LED1 off
  PORTD |= 1 << 1; //LED2 on

  timer = delay_short;
  while(timer--);
  PORTD &= ~(1 << 1); //LED2 off
  PORTD |= 1 << 2; //LED 3 on
  
  timer = delay_short;
  while(timer--);
  PORTD &= ~(1 << 2); //LED3 off
  
  timer = delay_long;
  while(timer--);
}

bool task2_flag = 0;
bool buton_prev = 0;
void task2(){
  //leduri pe PD 3-4
  //buton pe PB 0
  if((!buton_prev) && !(PINB & 1)){
    task2_flag = !task2_flag;
    buton_prev = 1;  
  }
  if(buton_prev && (PINB & 1)){
    buton_prev = 0;
  }
  if(task2_flag){
    PORTD = PORTD | (1 << 3); //set PD3
    PORTD = PORTD & ~(1 << 4); //reset PD4
  }
  else{
    PORTD = PORTD & ~(1 << 3); //reset PD3
    PORTD = PORTD | (1 << 4); //set PD4
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  task1();
  task2();
}
