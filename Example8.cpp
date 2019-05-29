#include "Example8.h"

ClassInheritingA::ClassInheritingA()
{
	ii = new int();
}

ClassInheritingA::~ClassInheritingA()
{
	*ii = -20;
}

ClassInheritingB::~ClassInheritingB()
{
	A = i = -10;
}

/*StructInheritingA::~StructInheritingA()
{
	__asm nop;
}*/

StructInheritingB::~StructInheritingB()
{
	A = i = -10;
}
int NCount = 0;
CNewClass::CNewClass()
{
	NCount++;
}

/*CNewClass::~CNewClass()
{
	NCount--;
}*/

static void InclVoid(); //Хотя бы одно упоминание ключевого слова static делает функцию статической

static void InclVoid()
{
	throw ClassInheritingB();
}

void Example8()
{
	/*try
	{
		//ClassInheritingA axx;
		//axx.i = 1;
		InclVoid();
		throw ClassInheritingB();
	}
	catch(ClassInheritingA ax)
	{
		__asm nop;
	}
	__asm nop;
    try
	{
		throw new ClassInheritingB();
	}
	catch(ClassInheritingA* ca)
	{
		__asm nop;
	}*/
	try
	{
		try
		{
			throw CNewClass();
		}
		catch(CNewClass& cl)
		{
			throw cl;
		}
	}
	catch(...)
	{

	}
	try
	{
		try
		{
			//throw new StructInheritingB;
			//throw;
			throw CNewClass();//протестировать с "фильтром"
			throw 1;
			//throw (char)1;
			*((int*)0) = 0;
		}
		catch(int i)
		{
			__asm nop;
		}
		/*catch(StructInheritingA* ca)
		{
		delete ca;
		}
		catch(StructInheritingB* cb)//поскольку структуры иерархически связаны, то вызывается ближайший обработчик
		{
		delete cb;
		}*/
		catch(...)
		{
			__asm nop;
			throw;
		}
	}
	catch(CNewClass&)//плохо из-за двойного вызова деструктора
	{

	}
}