#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <math.h>


#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  UCSR0A = 0;
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

// inicjalizacja ADC


FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;


    
  ADMUX = _BV(REFS0); // 5v and AnalogPort 0
  
  ADCSRA = 0b11000111; // prescaler 128

    
  while(1) {
      uint8_t low, high;
      ADCSRA |= _BV(ADSC); //set division 128
      while (ADCSRA & _BV(ADSC)); //wait for end of conversion

      low  = ADCL;
      high = ADCH;

      int output = ((int)(high<<8) | (int)low);

      float resistance = 10000*(1023/(float)output - 1); 
      
      /* T0/ R0
        36'C (310K) - 4000;
        22'C (295K) - 4800;

      4800 = 4000*e^(-B(1/310 - 1/295)
      ln(6/5) = -B*((295-310)/(310*295))
      ln(6/5) = B*15/310*295
      ln(6/5) = 3*B/18290
      18290*ln(6/5)/3 = B
      B = 1111.55.... 

      ln(R/4000) = -B(1/310 - 1/T)
      ln(R) - ln(4000) = B/T - B/310
      T(ln(R) - ln(4000) + B/310) = B
      T = B/(ln(R) - ln(4000) + B/310);
      T = 1111/[(ln(R) - 4.7]
      T = 1111/(ln(R) - 4.7);
      */

     
      
      float temp = (float)1111/(log(resistance) - 4.7);
      printf("%d\n", (int)temp);
  }

  return 0;
}

