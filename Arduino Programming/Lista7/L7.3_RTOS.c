#include <Arduino_FreeRTOS.h>

void setup()
{

  led_init();
  button_init();
  xTaskCreate(DancingLeds, "DancingLeds", 100, NULL, 1, NULL);
  xTaskCreate(DelayedButton, "DelayedButton", 100, NULL, 1, NULL);
}


void loop()
{
  // DO nothing
}

//####################
//#### DANCING LEDS ##

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

void led_init(){
  DDRB = PORTB = 0xff;
  _delay_ms(700);
  SetBit(0);
}

// ################
// ###############

// ################
// #### button ####

#define btn PD2
#define btn_pin PIND
#define N 100
#define led PD4
#define led_port PORTD

  uint8_t buffor[N];
  uint8_t it = 0;


void putClick(){
  buffor[it] = 1;
}


void putZero(){
  buffor[it] = 0;
}


void readClick(){
  if(buffor[it]) LEDOn();
  else LEDOff();
  
}

void updateIt(){
  if(++it == N) it = 0;
}


void LEDOn(){
  led_port |= 1<<led;
}

void LEDOff(){
  led_port &= ~(1<<led);
}


void button_init(){
  DDRD = (1<<led);
}

// ###############
// ###############




static void DancingLeds(void* pvParameters)
{
  while(1)
  {
    Switch(); 
  }
}


static void DelayedButton(void* pvParameters)
{
  while (1) {
    if(btn_pin & _BV(btn)){
        readClick();
        putClick();
        updateIt();  
    }
    else{
      readClick();
      putZero();
      updateIt();
    }


    _delay_ms(10);
  } 
}
