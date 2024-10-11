/*
 * Test03-Timer.c
 *
 * Created: 2024-10-11 오후 2:33:05
 * Author : user
 */
 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define DDR  DDRG
#define PORT PORTG
#define LED  PORTG1

int cnt= 0, cnt1 = 0, cntEx = 5, st = 0;
ISR(TIMER0_OVF_vect)
{
	cnt++;
	if(cnt > 25)	// (1/16M) * 256 *256 *25= 0.102 sec == 100ms초 간격
	{
		cnt = 0; 
		cnt1++; 
		if(cnt1 >= cntEx) 
		{
			cnt1 = 0;	
		
			if(st) 
			{
				PORT &= ~_BV(LED);
				st = 0;
			}
			else 
			{
				PORT |= _BV(LED);
				st = 1;
			}
		}
	}
}
ISR(INT0_vect)	//slower 
{
	cntEx++;
}
ISR(INT1_vect) //faster
{
	cntEx--;
	if (cntEx < 1) cntEx = 1;
}
int main(void)
{
	DDR |= _BV(LED);	//LED port 설정
	PORT |= _BV(LED);
	
	StandBy();
	
	PORT &= ~_BV(LED);
	
	TIMSK |= 0X01;	//TOIE0
	TCCR0 |= 0X06;	//분주비 1024 111, 분주비 256 110
	// External Interrupt 설정
	EIMSK |= 0x03;
	EICRA |= 0x0F;	
	sei();
    /* Replace with your application code */
	
    while (1) 
    {
    }
}

