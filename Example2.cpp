#include "Example2.h"

TestClassTwo::TestClassTwo() //��������� ���������� ����������
{
	int i = 0, j = 1;
	j /= i;
}

TestClassTwo::~TestClassTwo() //���������� �� ����������
{
	int i = 0, j = 1;
	j /= i;
}

void Example2()
{
	TestClassTwo* tst = nullptr;
	try
	{
		tst = new TestClassTwo(); //���������� �� ���������, ������ �� ����� �������, ���� ����� "���" � ���������� ������ ��������� ����������
								  //���������� ��������������� ������ ���� ���������� ���� \EHA, ���� "���"
	}
	catch(...)
	{
		delete tst; //tst �� ����� ���������������
	}
}