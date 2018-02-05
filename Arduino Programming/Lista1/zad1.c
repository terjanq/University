#include <avr/io.h>
#include <util/delay.h>



#define DELAY 100


uint8_t Direction=1;

void Switch() {
  if(PORTB & 0b00000001){
    Direction = 1;
  }
  if(PORTB & 0b00000100){
    Direction = 0;
  }

  if(Direction)
    PORTB <<= 1;
  else
    PORTB >>= 1;
  _delay_ms(DELAY);
}

void SetBit(uint8_t B){
  PORTB = 1 << B;
  _delay_ms(DELAY);
}



int main(void) {
 
  DDRB = PORTB = 0xff;
  _delay_ms(700);
  SetBit(0);
  while(1){
      Switch();    
  }                                                    /* end mainloop */
  return 0;
}