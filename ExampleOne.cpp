#include "ExampleOne.h"

TestClassOne::TestClassOne() //��������� ���������� ����������
{
	int i = 0, j = 1;
	j /= i;
}

TestClassOne::~TestClassOne() //���������� �� ����������
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
		__asm nop; //���������� ������ ���� ���������� /EHA (������ � ���������� SEH) ��� ����� ���������� "���"
	}
}