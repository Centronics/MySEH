#pragma once
#include "FuncDefTest.h"
#include "FuncDef.h"

inline void StaticIntDemo()
{
	StaticVar::StaticInt = 3;
	CallMe1();
	CallMe2();
}