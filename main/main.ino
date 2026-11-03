#include "header.h"
void setup() {
  // put your setup code here, to run once:
  // Punctul 1
    // PC:1-3 driver LED (pe anod)
  task1_setup();
  task2_setup();
  task3_setup();
  task4_setup();
  task5_setup();
  task6_setup();
}




void loop() {
  // put your main code here, to run repeatedly:
  task1();
  task2();
  task6();
  uint32_t cv = 1000000;
  while(cv--);
  cv = 1000000000;
}
