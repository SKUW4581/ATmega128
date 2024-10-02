/*
 * test01.c
 *
 * Created: 2024-10-02 오후 12:17:20
 * Author : user
 */ 
// LED Port : PG4
#include <avr/io.h>		//AVR 기본 헤더 


int main(void)
{
    /* Replace with your application code */
	//printf("hello world");
	DDRG |= 0x10;	// xxxx xxxx ==> 0001 0000; 1= 출력 0은 입력,즉 현재 4번 비트를 출력형태로 바꿈  xxx1 xxxx 5번째 비트만 출력으로 나오겠다 나머지 비트는 상관 x2진수를 GPIO 비트단위로 제어
    while (1) 
    {
		PORTG |= 0x10;	// 
	
    }
}

