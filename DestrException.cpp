#include "DestrException.h"

TestClass5::TestClass5()
{
	chr = new char[536870912];
}

TestClass5::~TestClass5()
{
	throw 1;
	*(int*)0 = 10;
}

void DestrExcpt()
{
	TestClass5* tmp = new TestClass5;
	try
	{
		delete tmp;//���� ��� ������������� /EHA ������ �� ��������� ��-�� ����������� ���������� �� �� ����� ����� � ��� �����������!
	}
	catch(...)
	{
		__asm nop;
	}
}