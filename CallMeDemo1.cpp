#include "FuncDef.h"

class X
{
	static int Y;
};

int X::Y = 9;

void CallMe1()
{
	CallMe();
	StaticVar::StaticInt = 9;
	//StaticVar::MyStaticVariableOld = 10;
	//StaticVar::MyStaticConstConstexpr = 11; // явл€етс€ константой.
}