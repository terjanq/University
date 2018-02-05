#include <avr/io.h>
#include <util/delay.h>

#define LA PB0
#define CLK PB5
#define SDI PB3

#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


//void myShiftOut(uint8_t val)
//{
//     uint8_t i;
//
//     for (i = 0; i < 8; i++)  {
//           bool state = !!(val & (1 << (7 - i)));
//           if(state) PORTB |= _BV(SDI);
//           else PORTB &= ~_BV(SDI);
//           PORTB |= _BV(CLK);
//           PORTB &= ~_BV(CLK);
//     }
//}



void SPI_MasterInit(void)
{
 /* Enable SPI, Master, set clock rate fck/16 */
 SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


void SPI_MasterTransmit(uint8_t cData)
{
 /* Start transmission */
 SPDR = cData;
 /* Wait for transmission complete */
 while(!(SPSR & (1<<SPIF)))
 ;
}

void SPI_SlaveInit(void)
{
 /* Set MISO output, all others input */
 DDR_SPI = (1<<DD_MISO);
 /* Enable SPI */
 SPCR = (1<<SPE);
}


char SPI_SlaveReceive(void)
{
 /* Wait for reception complete */
 while(!(SPSR & (1<<SPIF)))
 ;
 /* Return Data Register */
 return SPDR;
}




int main(){

   DDRB = 0xff;
   bool xswitch = false;
   int led_count = 6;
   int i = 0 ;

   SPI_MasterInit();
   SPI_SlaveInit();

   
  while(1){
        if(i==led_count - 1){
          i = 0;
          xswitch ^= true;
        }
        byte curb;
        if(xswitch) curb = 1 << (led_count- 1 - i);
        else curb = 1 << i;
        
         
         SPI_MasterTransmit(curb);
         PORTB &= ~_BV(LA); 
         PORTB |= _BV(LA);
        _delay_ms(100);
    i++;
  }
  
}

