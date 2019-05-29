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
		}//во всех случаях ведет себя одинаково: сначала вызывается блок завершения, затем обработчик исключения
	}
	__except(1)
	{
		__asm nop;
	}
}