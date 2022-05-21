//NOTE:- I am using Atmega32A, not Atmega328P at 1MHz
#include <avr/io.h>
#include <avr/interrupt.h>
////////////////////////////////////////////////////////
void initializeADC();
////////////////////////////////////////////////////////
int main()
{
  init();
  Serial.begin(9600);
  initializeADC();
  sei();
  
  

  while (1)
  {
    ADCSRA |= (1 << ADSC); 
    while (!(ADCSRA & (1 << ADIF))); 
    ADCSRA |= (1 << ADIF); 
    Serial.println(ADC); //Task 1
    _delay_ms(70);
  }
  return 0;
}
/////////////////////////////////////////////////////////////////////
void initializeADC()
{
  DDRA = 0x0;
  ADMUX = _BV(REFS0);
  ADCSRA = _BV(ADEN) | _BV(ADPS1) | _BV(ADPS0);
}
/////////////////////////////////////////////////////////////////////
