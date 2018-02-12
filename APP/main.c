#include "stm32f0xx.h"                  // Device header

unsigned char RamCode[80];
int i = 2;

void Add1Func(void) __attribute__((section("Add1Func")));

//void Add1Func(int *_Data) __attribute__((section(".ARM.__at_0x20000504")));

void Add10Func(void){
	i += 10;
}

void Add1Func(void) {
	i++;
}

/*****************************************************************************
Ö÷º¯Êý
******************************************************************************
*****************************************************************************/
int main(void)
{
	unsigned char *CodePtr;
	void (*AddFunc)(void);

	CodePtr = (unsigned char *)(Add1Func);
	for(i = 0; i < 40; i++){
		RamCode[i] = *CodePtr++;
	}
	CodePtr = (unsigned char *)(Add10Func);
	for(i = 40; i < 80; i++){
		RamCode[i] = *CodePtr++;
	}
	Add1Func();
	AddFunc = (void(*)(void))RamCode;
	AddFunc();
	AddFunc = (void(*)(void))(RamCode + 40);
	AddFunc();
	i = i;
	while(1);
}
