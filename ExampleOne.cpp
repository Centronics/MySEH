#include "ExampleOne.h"

TestClassOne::TestClassOne() //порождает аппаратное исключение
{
	int i = 0, j = 1;
	j /= i;
}

TestClassOne::~TestClassOne() //деструктор не выполнится
{
	int i = 0, j = 1;
	j /= i;
}

void ExampleOne()
{
	try
	{
		TestClassOne ert1;
	}
	catch(...)
	{
		__asm nop; //выполнится только если установлен /EHA (модель с поддержкой SEH) или когда установлен "НЕТ"
	}
}