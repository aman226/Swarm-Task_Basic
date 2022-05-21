//NOTE:- I am using Atmega32A, not Atmega328P at 1MHz
#include <avr/io.h>
#include <avr/interrupt.h>

void startBlink()
{

  OCR1A = 900; //Set 12499 for 3.2 seconds where P = 256 clk = 1Mhz
  TCCR1A = _BV(COM1A0);
  TCCR1B = _BV(WGM12) | _BV(CS12);
  PORTD |= _BV(PORTD5);

}

void stopBlink()
{
  PORTD &= ~_BV(PORTD5);
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 0;
}

ISR(INT0_vect)
{
  if (PIND & _BV(PIND2))
    startBlink();
  else
    stopBlink();
}

int main()
{
  DDRD |= _BV(DDD5);
  GICR = _BV(INT0); //External interrupt on PD2
  GIFR = _BV(INTF0);
  MCUCR = _BV(ISC00);

  if (PIND & _BV(PIND2))
    startBlink();
  sei();


  while (1)
  {

    
  }
  return 0;
}
