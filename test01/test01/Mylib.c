/*
 * Mylib.c
 *
 * Created: 2024-10-11 오후 2:38:22
 *  Author: user
 */ 
#include <avr/io.h>

int TestBit (char pin, char mask)	//PINx 레지스터의 값의 mask bit가 0인지 1인지 판별
{
	if (pin & mask != 0) return 1;		//해당핀과 mask가 0이 아니면 0
	return 0;
}

void StandBy() { // PG4 pin으로 프로그램 시작 스위치 연결
	DDRG &= ~0x10; // == "DDRG &= ~0x10;" | G4 입력 2)DDRG &= ~_BV(SW_STANDBY);
	PORTG |= 0X10; // == "PORTG |= 0X10;" | G4 내부저항 Pull Up 2)PORTG |= _BV(SW_STANDBY);
	
	while(!TestBit(PING, 0x10));
	while(TestBit(PING,0x10));

}

