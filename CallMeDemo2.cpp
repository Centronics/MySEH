#include "FuncDef.h"

void CallMe2()
{
	CallMe();
	StaticVar::StaticInt = 5;
}