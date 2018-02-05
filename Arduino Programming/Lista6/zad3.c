/*
Jan Góra Lista6
zad3 - sterowanie serwem modelarskim
*/

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem


// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

#define A1 DD5
#define A2 DD4



int wyp(uint16_t proc){
  return (proc*150)/100;
}




int main()
{

  // zainicjalizuj ADC
    adc_init();
  // mierz napięcie

  
    DDRD |= (1 << DDD6) | (1 << A1) | (1 << A2);


    //freq = 16000000/(2*150*1024) = 52

    OCR0A = 150;
    
    TCCR0A = 0;
    TCCR0A |= (1 << COM0B1);// set none-inverting mode, enable OR0B
    TCCR0A |= (1 << WGM00); //TOP value 0CR0A, PWM Phace Corrected
    TCCR0B |= (1 << WGM02);
    TCCR0B |= (1 << CS00) | (1 << CS02);  // set prescaler to 1024
    OCR0B = 20;
   
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint32_t v = ADC; // weź zmierzoną wartość (0..1023)
 
    OCR0B = (v*27)/1023 +7;   
    
  }
}
