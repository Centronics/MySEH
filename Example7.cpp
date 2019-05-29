#include "Example7.h"

TestClass12::TestClass12()
{
	Mas = nullptr;
	Mas = new char[536870912];
	Value = 0;
}

TestClass12::~TestClass12()
{
	if(Value == 6) delete Mas;
	Mas = nullptr;
	Value = 2;
}

void Example7()
{
	try
	{
		TestClass12 ert;
		ert.Value = 15;
		try
		{
			throw ert;
		}
		catch(TestClass12 tst) //создается копия объекта
		{
			tst.Value = 6;
			throw tst;
		}
	}
	catch(TestClass12 tst)
	{
		tst.Value = 7;
	}
}