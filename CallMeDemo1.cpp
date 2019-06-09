#include "FuncDef.h"

void CallMe1()
{
	CallMe();
	StaticVar::StaticInt = 9;
}