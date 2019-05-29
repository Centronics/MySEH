#include "ConstrException.h"

TestClass6::TestClass6()
{
	*(int*)0 = 10;
}

TestClass7::TestClass7()
{
	chr = new char[536870912];
}

TestClass7::~TestClass7()
{
	delete chr;
}

void ConstrExpt()
{
	TestClass6* tcl6;
	try
	{
		TestClass7 tcl7;
		tcl6 = new TestClass6;
	}
	catch(...)
	{
		__asm nop;
	}
}