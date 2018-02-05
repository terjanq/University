#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

//#define F_CPU 16000000UL
#define BAUDRATE 9600

volatile bool toggle = false;
volatile bool pushes[100];
volatile int it = 0;


ISR(TIMER1_COMPA_vect){
  
  if(pushes[it]) PORTB |= (1<<PB1);
  else PORTB &= ~(1<<PB1);
  
  if(PINB & (1<<PB2)) pushes[it] = true;
  else pushes[it] = false;

  it++;
  it%=100;
}

void timer_interrupt_init(void)
{

 cli();
    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 156;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

  

    sei();
}

int main(){

    timer_interrupt_init();   // Initailise USART 0 to use the receive interrupt

    set_sleep_mode(SLEEP_MODE_IDLE);
   
    sleep_enable();
    sleep_mode();
    
    DDRB = 0b10;
    PORTB = 0b110;
    while(1)
    {
      sleep_mode();
    }
        
    }
