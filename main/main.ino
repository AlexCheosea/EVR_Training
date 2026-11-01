//TODO : Macro uri pentru leduri 1-8 pe PORTD
//TODO : Macro uri pentru butoane pe PORTB
//TODO : Fisiere separate: functii, header, main
#include "header.h"
void setup() {
  // put your setup code here, to run once:
  // Punctul 1
    // PC:1-3 driver LED (pe anod)
  task1_setup();
  task2_setup();
  task3_setup();
}




void loop() {
  // put your main code here, to run repeatedly:
  task1();
  task2();
}
