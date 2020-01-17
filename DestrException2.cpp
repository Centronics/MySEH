#include "DestrException2.h"

TestClass10::~TestClass10()
{
	*(int*)0 = 0;
}

TestClass11::~TestClass11()
{
	*(int*)0 = 0;
}

void DestrExptEx2()
{
	a:
	try
	{
		TestClass10 tcl10; // Второй деструктор будет вызван даже в случае исключения в первом.
		TestClass11 tcl11;
		goto a;
	}
	catch(...)
	{
		__asm nop;
	}
}

void DestrExptEx3()
{
	a:
	try
	{
		TestClass10 tcl10;
		try
		{
			TestClass11 tcl11;
			goto a;
		}
		catch(...)
		{
			__asm nop;
		}
	}
	catch(...)
	{
		__asm nop;
	}
}