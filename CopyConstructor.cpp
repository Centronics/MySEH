#include "CopyConstructor.h"

CpyA& CpyA::operator=(CpyA&)
{
	__asm nop;
}

CpyC::CpyC()
{
	i = 0;
}

CpyA::CpyA()
{
	__asm nop;
}

CpyB::CpyB() : ca(), cc()
{
	__asm nop;
}

CpyB::CpyB(CpyB& cb) : ca(), cc()
{
	__asm nop;
	//(*this) = cb;
	ca = cb.ca; //���������: ��� ��������� ����� �������
	cc = cb.cc;
}

void CopyTestFunction()
{
	CpyB cb;
	CpyB cb1;
	cb = cb1;
	CpyB gb(cb);
	CpyB db = cb; //���������: ����������� ����������� � ��� ��������� ����� �������
}