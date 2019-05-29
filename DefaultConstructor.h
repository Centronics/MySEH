#pragma once

class A
{
public:
	A()
	{
		_asm nop;
	}

	A(int) : i(20)
	{
		_asm nop;
	}

	A(double) : d(9.9), i(30)
	{
		_asm nop;
	}

	double d = 1.1;
	int i = 10;
};

inline void DefaultConstructorDemo()
{
	A a;      // d = 1.1; i = 10;
	A n(50);  // d = 1.1; i = 20;
	A b(2.2); // d = 9.9; i = 30;
}