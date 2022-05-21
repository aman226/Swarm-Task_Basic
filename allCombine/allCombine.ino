//NOTE:- I am using Atmega32A, not Atmega328P at 1MHz
#include <avr/io.h>
#include <avr/interrupt.h>
////////////////////////////////////////////////////////
void startBlink();
void stopBlink();
void initializeADC();
void initializeExtInterrupt();
////////////////////////////////////////////////////////
int main()
{
  init();
  Serial.begin(9600);
  DDRD |= _BV(DDD5);
  initializeExtInterrupt();
  initializeADC();
  if (PIND & _BV(PIND2))
    startBlink();

  sei();


  while (1)
  {
    char buffer[6];
    ADCSRA |= (1 << ADSC); 
    while (!(ADCSRA & (1 << ADIF))); 
    ADCSRA |= (1 << ADIF);
    Serial.println(ADC); 
    _delay_ms(30);
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
void initializeExtInterrupt()
{
  GICR = _BV(INT0); //External interrupt on PD2
  GIFR = _BV(INTF0);
  MCUCR = _BV(ISC00);  
}
/////////////////////////////////////////////////////////////////////
void startBlink()
{
  
  OCR1A = 900; //Set 12499 for 3.2 seconds where P = 256 clk = 1Mhz
  TCCR1A = _BV(COM1A0);
  TCCR1B = _BV(WGM12) | _BV(CS12);
  PORTD |= _BV(PORTD5);

}
///////////////////////////////////////////////////////////////////////
void stopBlink()
{
  PORTD &= ~_BV(PORTD5);
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 0;
}
////////////////////////////////////////////////////////////////////////
ISR(INT0_vect)
{
  if (PIND & _BV(PIND2))
    startBlink();
  else
    stopBlink();
}
