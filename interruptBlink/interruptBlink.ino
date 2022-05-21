//NOTE:- I am using Atmega32A, at 1MHz -> Internal Oscillator

#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER1_COMPA_vect)
{
  PORTB ^= _BV(PORTB5);
}


int main()
{
  DDRB = _BV(DDB5);
  //DDRD = _BV(DDD5);
  
  OCR1A = 12499; // P = 256 clk = 1Mhz
  
  TCCR1A = _BV(COM1A0);
  TCCR1B = _BV(WGM12) | _BV(CS12);

  TIMSK = _BV(OCIE1A);
  PORTB ^= _BV(PORTB5);
  
  sei();


  while (1)
  {

  }
  return 0;

}
