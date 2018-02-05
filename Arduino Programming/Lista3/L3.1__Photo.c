#include <avr/io.h>
#include <util/delay.h>


int main(){



    //10k ohm resistor
    
    DDRB = 0b0010; // PB1 
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10); // compare-mode, FAST PWM / WGM10 & WGM12 - fast mode 0xff
    TCCR1B = _BV(CS10) | _BV(WGM12) ; // CLOCK / 64
  
    ADMUX = _BV(REFS0); // 5v and AnalogPort 0
 
    ADCSRA = 0b11000111;

    
    while(1){
      uint8_t low, high;
      ADCSRA |= _BV(ADSC); //set division 128
      while (ADCSRA & _BV(ADSC)); //wait for end of conversion

      low  = ADCL;
      high = ADCH;

      int output = ((int)(high<<8) | (int)low);

      // R1 = 10 000
      // R = (Ui/Uo * R1) - R1 = R1(Ui/Uo - 1);
      // ADC = U/Aref * 1023
      // U = (ADC*Aref) / 1023
      // Ui / Uo = (Aref * 1023)/ADC * Aref
      // Ui / Uo = 1023/ADC


      float resistance = 100*(1023/(float)output - 1); // resistance / 1000

     

      uint8_t out = (float)(1 - resistance/1400)*255;

      OCR1A = out;

    }



  return 0;
}
