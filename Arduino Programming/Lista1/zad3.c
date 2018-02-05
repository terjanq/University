#include <avr/io.h>
#include <util/delay.h>



  void s(uint8_t b[]){

    for(uint8_t i = 0; i<6; i++){
      PORTB = b[i];
      _delay_ms(10);
    }
    
  }


void printW(uint8_t a[], uint8_t sizeW){
  for(int i=0; i<sizeW; i++){
    s(a[i]);
  }
}

  
int main(void) {

  
  DDRB = 0xff;
  uint8_t wordW[] = {0,3,1,3,2,3};
  while(1){

    // OLA



    uint8_t alfabet[][6] = {
      {0b00011111,0b00010001,0b00010001,0b00010001,0b00010001,0b00011111},
      {0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00011111},
      {0b00011111,0b00010001,0b00010001,0b00011111,0b00010001,0b00000000},
      {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}};
    

      
      printW(wordW, 6);


    
  }
  return 0;
}