#include <avr/io.h>
#include <util/delay.h>

#define btn PD2
#define btn_pin PIND
#define N 100
#define led PD3
#define led_port PORTD

  uint8_t buffor[N];
  uint8_t it = 0;


void putClick(){
  buffor[it] = 1;
}


void putZero(){
  buffor[it] = 0;
}


void readClick(){
  if(buffor[it]) LEDOn();
  else LEDOff();
  
}

void updateIt(){
  if(++it == N) it = 0;
}


void LEDOn(){
  led_port |= led;
}

void LEDOff(){
  led_port &= ~led;
}



int main(void) {
               
  DDRD = led;
  
  while (1) {
    if(btn_pin & _BV(btn)){
        readClick();
        putClick();
        updateIt();  
    }
    else{
      readClick();
      putZero();
      updateIt();
    }


    _delay_ms(10);
  }                                                   
  return 0;
}