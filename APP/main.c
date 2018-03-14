#include "stm32f0xx.h"                  // Device header

unsigned char RamCode[80];
int i = 2;

void Add1Func(void) __attribute__((section("Add1Func")));

//void Add1Func(int *_Data) __attribute__((section(".ARM.__at_0x20000504")));

void Add100Func(void){
	i += 100;
}

void Add10Func(void){
	i += 10;
	Add1Func();
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

	CodePtr = (unsigned char *)(Add10Func) - 1;
	for(i = 0; i < 80; i++){
		RamCode[i] = CodePtr[i];
	}

	AddFunc = Add10Func;
	AddFunc();
	AddFunc = (void(*)(void))((unsigned char *)RamCode - 1);
	AddFunc();
	i = i;
	while(1);
}
