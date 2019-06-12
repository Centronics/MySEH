#include "FuncDef.h"

void CallMe2()
{
	CallMe();
	StaticVar::StaticInt = 5;
	//StaticVar::MyStaticVariableOld = 50;
	//StaticVar::MyStaticConstConstexpr = 11; // явл€етс€ константой.
}