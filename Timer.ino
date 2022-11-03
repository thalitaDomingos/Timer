#define LED PD7

int contador = 0;

ISR (TIMER0_OVF_vect) {
  if (contador >= 61) {
    PORTD ^= (1 << LED); // inverte o estado do LED
    contador = 0;
  }
  contador ++;
}

int main(void)
{
  DDRD |= (1 << LED); // led como saída
  //TCCR0A = 0;
  TCCR0B = (1 << CS02) | (1 << CS00); // clock interno com freq de 16MHz/1024 = 15,625kHz

  // período: T = (1 / 15625) = 64us
  // 8 bits = 2^3 = 256 -> 0 a 255
  // 255 * 64u = 16,32ms
  // Regra de 3:
  // 1 int ------ 16,32ms
  // x int ------   1s
  // x = 61 interrupções

  TIMSK0 |= (1 << TOIE0); // liga a interrupção no fim da contagem
  sei();                  // Habilita a interrupção global

  while (1) {
  }
}
