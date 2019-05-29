#include "Example6.h"

TestClass8::~TestClass8()
{
	__asm nop;
}

TestClass9::~TestClass9()
{
	__asm nop;
}

TestClass9::TestClass9()
{
	*(int*)0 = 0;
}

void Example6()
{
	try
	{
		TestClass8 clc;
		try
		{
			TestClass9 cl9;
			throw cl9;
		}
		catch(...)
		{
			//throw;
		}
	}
	catch(TestClass9 i)
	{
		__asm nop;
	}
}