#include <avr/io.h>
#include <util/delay.h>



#define btn_reset PC0
#define btn_next PC1
#define btn_prev PC2

#define btns PINC
#define LEDs PORTB

  uint8_t a = 0;
  uint8_t gray;

void nextGray(){
  if(a == 15){
    a = 0;
  }
  else{
     a++;
  }

  gray = a ^ (a >> 1);
  PORTB = gray;
  
}


void prevGray(){
  if(a == 0){
    a = 15;
  }
  else{
    a--;
  }
  gray = a ^ (a >> 1);
  PORTB = gray;
}


void resetGray(){
  a = 0;
  PORTB = 0;
}

int main(void) {
 
  DDRB = 0xff;
  DDRC = 0;

  uint8_t clickedPrev = 0;
  uint8_t clickedNext = 0;
  
  while(1){
      if(btns & _BV(btn_reset)){
        resetGray();
      }

      
        if(btns & _BV(btn_next)){
          if(!clickedNext){
            clickedNext = 1;
            nextGray();
          }
 
        }
        else
          clickedNext = 0;
          
        if(btns & _BV(btn_prev)){
          if(!clickedPrev){
            clickedPrev = 1;
            prevGray();
          }
        }
        else
          clickedPrev = 0;
      _delay_ms(10);
  }                                                    /* end mainloop */
  return 0;
}