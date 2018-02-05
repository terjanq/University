#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

//#define F_CPU 16000000UL
#define BAUDRATE 9600



volatile char znak;
volatile uint8_t StrRxFlag=0;

void USART_send();

ISR(USART_RX_vect){
    znak=UDR0;         
    StrRxFlag = 1;
}

void USART_send( unsigned char data)
{

    UDR0 = data;
}




void USART_interrupt_init(void)
{
    cli();

    #define BAUD_PRESCALER ((F_CPU)/16/BAUDRATE - 1)
 
    UBRR0 = BAUD_PRESCALER;                
    UCSR0B = ((1<<RXEN0)|(1<<TXEN0)|(1 << RXCIE0));      
    UCSR0C = ((1 << UCSZ01)|(1<<UCSZ00)); 
    UCSR0A = 0;
    sei();
}

int main(){

    USART_interrupt_init();   // Initailise USART 0 to use the receive interrupt

    set_sleep_mode(SLEEP_MODE_IDLE);
    PRR = ~(1 << PRUSART0);
    
    while(1)
    {
        sleep_mode();
        sleep_enable();
        
        if(StrRxFlag)
        {
            USART_send(znak);                    
            StrRxFlag=0;
                          
        }
        else{
          USART_send("nothing");
        }



 
    }
}
