#include <avr/io.h>
#include <util/delay.h>

// Pin 6  (PD6) -> Dioda IR // OC2B
// Pin 4 (PD4) <- Odbiornik IR
// Pin 2 (PD2) -> Dioda LED

unsigned long timer_freq;
enum t0_prescaler
{
    T0_PRESCALER_1 = _BV(CS00),
    T0_PRESCALER_8 = _BV(CS01),
    T0_PRESCALER_64 = _BV(CS00) | _BV(CS01),
    T0_PRESCALER_256 = _BV(CS02),
    T0_PRESCALER_1024 = _BV(CS02) | _BV(CS00),
};

static void t0_set_prescaler(enum t0_prescaler ps)
{
    TCCR0B = ps;
}

static unsigned short t0_get_prescaler_rate(enum t0_prescaler ps)
{
    unsigned short rate;
    switch(ps)
    {
        case T0_PRESCALER_1:
            rate = 1;
            break;
        case T0_PRESCALER_8:
            rate = 8;
            break;
        case T0_PRESCALER_64:
            rate = 64;
            break;
        case T0_PRESCALER_256:
            rate = 256;
            break;
        case T0_PRESCALER_1024:
            rate = 1024;
            break;
        default:
            rate = 0;
            break;
    }
    return rate;
}

static unsigned long div_round(unsigned long d, unsigned long q)
{
    return (d + (q/2)) / q;
}

static void t0_set_ctc_a(unsigned long hz)
{
    OCR0A = div_round(timer_freq, hz*2) - 1;
    TCCR0A =
          _BV(COM0A0) // toggle
        | _BV(WGM01); // CTC
}

int main(){

    enum t0_prescaler ps = T0_PRESCALER_256;
    DDRD = 0;
    DDRD |= _BV(DDD6) | _BV(PD2);
    
    t0_set_prescaler(ps);
    timer_freq = div_round(F_CPU, t0_get_prescaler_rate(ps));

    
   t0_set_ctc_a(36000);
    long long i = 0;
    while (1){
   
    if (PIND & _BV(PD4)) {;
        PORTD &= ~_BV(PD2);
    }
            else {
              PORTD |= _BV(PD2);
            }
    } 

   
 
    _delay_ms(10);

    
    return 0;
}

