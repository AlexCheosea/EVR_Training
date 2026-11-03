
#include "header.h"

// Task 1: LEDs on PC1, PC2, PC3
volatile uint32_t timer = 0;

void task1_setup() {
    DDRC |= _BV(DDC1) | _BV(DDC2) | _BV(DDC3); //PC 0-3 output

    PORTC &= ~(_BV(PC1) | _BV(PC2) | _BV(PC3)); //PC 0-3 low
}

void task1() {
    LED0_set();
    timer = DELAY_SHORT;
    while (timer--);
    LED0_reset();

    LED1_set();
    timer = DELAY_SHORT;
    while (timer--);
    LED1_reset();

    LED2_set();
    timer = DELAY_SHORT;
    while (timer--);
    LED2_reset();

    timer = DELAY_LONG;
    while (timer--);
}

// Task 2: LEDs on PD7 and PD2, button on PD4
bool task2_flag = false;
bool button_previous = false;

void task2_setup() {
    DDRD |= _BV(DDD7) | _BV(DDD2); //PD 2,7 output

    DDRD &= ~_BV(DDD4); //PD 4 input
    PORTD |= _BV(PD4);  //PD 4 pullup
}

void task2() {
    if (!button_previous && !btn0) {
        task2_flag = !task2_flag;
        button_previous = true;
    }

    if (button_previous && btn0) {
        button_previous = false;
    }

    if (task2_flag) {
        LED3_set();
        LED4_reset();
    } else {
        LED3_reset();
        LED4_set();
    }
}

// Task 3: LED on PD5, button on PD3 / INT1
void task3_setup() {
    DDRD |= _BV(DDD5); //PD5 output

    DDRD &= ~_BV(DDD3); //PD3 input
    PORTD |= _BV(PD3); //PD3 pullup

    // INT1: falling edge
    cli();
    EICRA &= ~_BV(ISC10);  // Clear ISC10
    EICRA |= _BV(ISC11);   // Set ISC11

    EIMSK |= _BV(INT1);
    sei();
}

ISR(INT1_vect) {
    LED5_toggle();
}

// Task 4: Timer2 CTC, reuses Task1 LEDs
typedef enum {
    STEP0,
    STEP1,
    STEP2,
    STEP3
} task4_step;

volatile task4_step current_step = STEP0;

void task4_setup() {
    task1_setup();

    TCCR2A = _BV(WGM21); //mod CTC
    TCCR2B = 0;          //opreste timer
    TCNT2 = 0;          //reseteaza counter

    OCR2A = T2_COMPARE; //valoare comparatie

    TIFR2 = _BV(OCF2A); //clear flag intrerupere
    TIMSK2 |= _BV(OCIE2A); //enable intrerupere A

    // Prescaler = 1024
    TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
}

ISR(TIMER2_COMPA_vect) {
    switch (current_step) {
        case STEP0:
            LED0_reset();
            LED1_reset();
            LED2_reset();
            break;

        case STEP1:
            LED0_set();
            break;

        case STEP2:
            LED1_set();
            break;

        case STEP3:
            LED2_set();
            break;

        default:
            current_step = STEP0;
            break;
    }

    current_step = current_step + 1;

    if (current_step > STEP3) {
        current_step = STEP0;
    }
}

// Task 5: Hardware Fast PWM on PB1 / OC1A
// Timer1 Mode 14, TOP = 399, prescaler = 1
// PWM frequency = 400000 / 400 = 1000 Hz

volatile uint16_t task5_duty = 0;
volatile int8_t task5_direction = 1;
volatile uint8_t task5_divider = 0;

static void task5_apply_duty() {
    if (task5_duty == 0) {
        TCCR1A &= ~_BV(COM1A1);
        PORTB &= ~_BV(PB1);
    }
    else if (task5_duty >= 399) {
        TCCR1A &= ~_BV(COM1A1);
        PORTB |= _BV(PB1);
    }
    else {
        OCR1A = task5_duty;
        TCCR1A |= _BV(COM1A1);
    }
}

void task5_setup() {
    DDRB |= _BV(DDB1); //PB 1 output
    PORTB &= ~_BV(PB1);//PB 1 low

    //Reset config Timer1
    TCCR1A = 0; 
    TCCR1B = 0;
    TCNT1 = 0;

    ICR1 = TASK5_PWM_TOP;
    OCR1A = 0;

    // Fast PWM Mode 14, non-inverting OC1A
    TCCR1A = _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

    task5_duty = 0;
    task5_direction = 1;
    task5_divider = 0;
    cli();
    TIFR1 = _BV(TOV1);
    TIMSK1 |= _BV(TOIE1);
    sei();
}


ISR(TIMER1_OVF_vect) {
    if (++task5_divider < 127) { //update brightness every x periods
        return;
    }

    task5_divider = 0;

    if (task5_direction > 0) {
        if (task5_duty >= 395) {
            task5_duty = 399;
            task5_direction = -1;
        } else {
            task5_duty += 4;
        }
    }
    else {
        if (task5_duty <= 4) {
            task5_duty = 0;
            task5_direction = 1;
        } else {
            task5_duty -= 4;
        }
    }

    task5_apply_duty();
}
// Task 6: ADC0 potentiometer on PC0
// Hardware Fast PWM on PD6 / OC0A
void task6_setup() {
    // PC0: ADC input
    DDRC &= ~_BV(DDC0);
    PORTC &= ~_BV(PC0);

    // PD6: PWM output
    DDRD |= _BV(DDD6);
    PORTD &= ~_BV(PD6);

    // ADC0, AVcc reference, prescaler 4
    ADMUX = _BV(REFS0);
    ADCSRA = _BV(ADEN) | _BV(ADPS1);

    // Timer0 Fast PWM, TOP = 255
    // Non-inverting OC0A, prescaler = 1
    TCCR0A = _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B = _BV(CS00);

    OCR0A = 0;

    TIMSK0 = 0;
}

void task6() {
    ADCSRA |= _BV(ADSC);

    while (ADCSRA & _BV(ADSC));

    OCR0A = ADC >> 2;
}
