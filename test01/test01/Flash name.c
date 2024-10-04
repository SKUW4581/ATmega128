#define F_CPU 16000000UL
// Switch 1 : PG3, Input (mode 1)
// Switch 2 : PG2, Input (mode 2)
// Switch 3 : PG1, Input (mode 3)
// LED Port : PG4, Output

#include <avr/io.h>    // AVR 기본 헤더
#include <util/delay.h>

int Check(int* n_speed)
{
	char v3 = PING & 0x08;
	if ( v3 == 0 )
	{
		*n_speed += 1;
	}
	
	char v2 = PING & 0x04;
	if ( v2 == 0 )
	{
		*n_speed -= 1 ;
		if (*n_speed < 0)
		{
			*n_speed = 0;
		}
	}
	
	char v1 = PING & 0x02;
	if (v1 == 0) return 1;
	return 0;
}

int main(void)
{
	// PG4 (4번 비트)를 출력으로 설정, PG3, PG2, PG1은 입력으로 설정
	DDRG |= 0x10;       // PG4: LED 제어를 위해 출력으로 설정
	DDRG &= ~(0x08);    // PG3: Switch 1 입력 (mode 1)
	DDRG &= ~(0x04);    // PG2: Switch 2 입력 (mode 2)
	DDRG &= ~(0x02);    // PG1: Switch 3 입력 (mode 3)
	
	//int mode = 0;       
	int toggle = 0;// 기본적으로 LED를 끈 상태로 시작
	int n_speed = 4;
	// 무한 루프
	while (1)
	{
		if(Check(&n_speed)){
			PORTG &= ~0x10;
			if (toggle == 1)   toggle = 0;
			else            toggle = 1;
			_delay_ms(300);
		}
		if(toggle){
			if (PORTG & 0x10) // LED가 켜져있다면
			{
				PORTG &= ~0x10; // 끄고
			} else // 아니라면
			{
				PORTG |= 0x10; // 켜라
			}
			for (int i = 0; i < n_speed; i++)
			{
				_delay_ms(50);	
			}
		}
	}
}
