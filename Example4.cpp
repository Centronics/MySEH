#include "Example4.h"
#include <Windows.h>

void Example4()
{
	__try
	{
		__try
		{
			//*(int*)0 = 0;
			__asm nop;
		}
		__finally
		{
			if(!AbnormalTermination())
				__asm nop;
			else
				__asm nop;
		}//�� ���� ������� ����� ���� ���������: ������� ���������� ���� ����������, ����� ���������� ����������
	}
	__except(1)
	{
		__asm nop;
	}
}