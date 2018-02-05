/*
Jan Góra Lista6
zad1 - sterowanie silnkiem
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


int main()
{

  // zainicjalizuj ADC
    adc_init();
  // mierz napięcie

    DDRD |= (1 << DDD6);
    // PD6 is now an output
    OCR0A = 0;
    // set PWM for 50% duty cycle
    TCCR0A |= (1 << COM0A1);
    // set none-inverting mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode
    TCCR0B |= (1 << CS01);
    // set prescaler to 8 and starts PWM
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    OCR0A = v/4;
    
  }
}
